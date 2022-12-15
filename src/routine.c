/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:49 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/15 16:53:03 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	change_status(t_main *main, t_phi *phi, int status)
{
	if (pthread_mutex_lock(&main->status))
		ft_error(main, MUTEX_ERR);
	phi->status = status;
	if (pthread_mutex_unlock(&main->status))
		ft_error(main, MUTEX_ERR);
}

void	check_death(t_main *main, t_phi *phi)
{
	long long	current_time;

	current_time = get_time_ms();
	if (pthread_mutex_lock(&main->eat))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_lock(&main->status))
		ft_error(main, MUTEX_ERR);
	if (phi->status != EAT && current_time - phi->last_eat >= main->t_die)
	{
		if (pthread_mutex_lock(&main->write))
			ft_error(main, MUTEX_ERR);
		main->is_dead = YES;
		printf("%lld %d %s\n", current_time - main->t_start, phi->id + 1, DIED);
		if (pthread_mutex_unlock(&main->write))
			ft_error(main, MUTEX_ERR);
	}
	if (pthread_mutex_unlock(&main->status))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_unlock(&main->eat))
		ft_error(main, MUTEX_ERR);
}

void	check_end(t_main *main)
{
	int	i;

	while (main->is_dead == NO && main->is_max_eat == NO)
	{
		i = -1;
		usleep(100);
		while (++i < main->n_phi)
		{
			check_death(main, &main->phi[i]);
			if (main->is_dead == YES)
				break ;
			if (pthread_mutex_lock(&main->full))
				ft_error(main, MUTEX_ERR);
			if (main->nb_phi_full == main->n_phi)
			{
				if (pthread_mutex_lock(&main->write))
					ft_error(main, MUTEX_ERR);
				main->is_max_eat = YES;
				if (pthread_mutex_unlock(&main->write))
					ft_error(main, MUTEX_ERR);
			}
			if (pthread_mutex_unlock(&main->full))
				ft_error(main, MUTEX_ERR);
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
	while (main->is_dead == NO && main->is_max_eat == NO)
	{
		eating(main, phi);
		if (main->is_dead == YES || main->is_max_eat == YES)
			break ;
		sleeping(main, phi, phi->id);
		thinking(main, phi, phi->id);
	}
	return (NULL);
}
