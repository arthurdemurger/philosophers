/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:49 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/17 18:28:55 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_main *main, t_phi *phi)
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
	ft_usleep(main->t_die);
}

void	check_end(t_main *main)
{
	int	i;

	while (main->is_dead == NO && main->is_max_eat == NO)
	{
		i = -1;
		while (++i < main->n_phi)
		{
			check_death(main, &main->phi[i]);
			if (main->is_dead == YES)
				break ;
			else if (main->nb_phi_full == main->n_phi)
			{
				if (pthread_mutex_lock(&main->write))
					ft_error(MUTEX_ERROR);
				main->is_max_eat = YES;
				if (pthread_mutex_unlock(&main->write))
					ft_error(MUTEX_ERROR);
			}
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
		ft_usleep(main->t_die);
		return (NULL);
	}
	if (phi->id % 2 == 0)
		ft_usleep(10);
	while (main->is_dead == NO && main->is_max_eat == NO)
	{
		eating(main, phi);
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
