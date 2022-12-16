/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:49 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/16 14:34:14 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	change_status(t_main *main, t_phi *phi, int status)
{
	mutex_lock(main, &main->status);
	phi->status = status;
	mutex_unlock(main, &main->status);
}

void	check_death(t_main *main, t_phi *phi)
{
	long long	current_time;

	current_time = get_time_ms();
	mutex_lock(main, &main->eat);
	mutex_lock(main, &main->status);
	if (phi->status != EAT && current_time - phi->last_eat >= main->t_die)
	{
		mutex_lock(main, &main->write);
		main->is_dead = YES;
		printf("%lld %d %s\n", current_time - main->t_start, phi->id + 1, DIED);
		mutex_unlock(main, &main->write);
	}
	mutex_unlock(main, &main->status);
	mutex_unlock(main, &main->eat);
}

void	check_end(t_main *main)
{
	int	i;

	while (1)
	{
		i = -1;
		usleep(100);
		while (++i < main->n_phi)
		{
			check_death(main, &main->phi[i]);
			mutex_lock(main, &main->write);
			if (main->is_dead == YES)
			{
				mutex_unlock(main, &main->write);
				return ;
			}
			mutex_unlock(main, &main->write);
			mutex_lock(main, &main->full);
			if (main->nb_phi_full == main->n_phi)
			{
				mutex_lock(main, &main->write);
				main->is_max_eat = YES;
				mutex_unlock(main, &main->write);
				mutex_unlock(main, &main->full);
				return ;
			}
			mutex_unlock(main, &main->full);
		}
	}
}

void	*routine(void *arg)
{
	t_phi	*phi;
	t_main	*main;

	phi = (t_phi *) arg;
	main = phi->main;
	if (main->n_phi == 1)
	{
		put_action(main, phi->id, FORK);
		ft_usleep(main, main->t_die);
		return (NULL);
	}
	if (phi->id % 2)
		ft_usleep(main, 50);
	while (1)
	{
		mutex_lock(main, &main->write);
		if (main->is_dead == YES && main->is_max_eat == YES)
		{
			mutex_unlock(main, &main->write);
			break ;
		}
		mutex_unlock(main, &main->write);
		eating(main, phi);
		if (main->is_dead == YES || main->is_max_eat == YES)
			break ;
		sleeping(main, phi, phi->id);
		thinking(main, phi, phi->id);
	}
	return (NULL);
}
