/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:49 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 16:09:29 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_main *main, t_phi *phi)
{
	long long	current_time;

	current_time = get_time_ms();
	if (pthread_mutex_lock(&main->eat))
		ft_error(MUTEX_ERROR);
	if (current_time - phi->last_eat >= main->t_die)
	{
		if (pthread_mutex_lock(&main->write))
			ft_error(MUTEX_ERROR);
		main->is_dead = YES;
		printf("%lld %d %s\n", current_time - main->t_start, phi->id + 1, DIED);
		if (pthread_mutex_unlock(&main->write))
			ft_error(MUTEX_ERROR);
	}
	if (pthread_mutex_unlock(&main->eat))
		ft_error(MUTEX_ERROR);
	if (main->is_dead == YES)
		return (1);
	return (0);
}

int	check_end(t_main *main)
{
	int	i;

	while (main->is_dead == NO && main->is_max_eat == NO)
	{
		i = -1;
		while (++i < main->n_phi)
		{
			check_death(main, &main->phi[i]);
			if (main->is_dead == YES)
				return (0);
			else if (main->nb_phi_full == main->n_phi)
			{
				if (pthread_mutex_lock(&main->write))
					ft_error(MUTEX_ERROR);
				main->is_max_eat = YES;
				if (pthread_mutex_unlock(&main->write))
					ft_error(MUTEX_ERROR);
				return (0);
			}
		}
	}
	return (1);
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
		ft_usleep(main->t_die);
		return (NULL);
	}
	while (main->is_dead == NO)
	{
		eating(main, phi);
		put_action(main, phi->id, EATING);
		if (main->is_max_eat)
			break ;
		sleeping(main, phi->id);
		put_action(main, phi->id, THINKING);
	}
	return (NULL);
}

void	start_eat(t_main *main)
{
	int	i;

	i = -1;
	main->t_start = get_time_ms();
	while (++i < main->n_phi)
	{
		main->phi[i].last_eat = main->t_start;
		if (pthread_create(&main->phi[i].th_id, NULL, routine, &main->phi[i]))
			ft_error(PTHREAD_ERROR);
	}
	check_end(main);
	i = -1;
	while (++i < main->n_phi)
		if (pthread_join(main->phi[i].th_id, NULL))
			ft_error(PTHREAD_ERROR);
}
