/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:51:25 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 22:43:06 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	sleeping(t_main *main)
{
	ft_usleep(main->t_sleep, main);
}

void	eating(t_main *main, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fk))
		ft_error(MUTEX_ERROR);
	put_action((t_main *)philo->main, philo->id, FORK);
	if (pthread_mutex_lock(&philo->r_fk))
		ft_error(MUTEX_ERROR);
	put_action((t_main *)philo->main, philo->id, FORK);
	if (pthread_mutex_lock(&main->eating))
		ft_error(MUTEX_ERROR);
	put_action((t_main *)philo->main, philo->id, EATING);
	philo->last_eat = get_time_ms();
	if (++philo->n_eat == main->n_max_eat)
		main->is_max_eat = YES;
	if (pthread_mutex_unlock(&main->eating))
		ft_error(MUTEX_ERROR);
	ft_usleep(main->t_eat, main);
	if (pthread_mutex_unlock(&philo->r_fk))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_unlock(&philo->l_fk))
		ft_error(MUTEX_ERROR);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)arg;
	main = philo->main;
	if (!(philo->id % 2 == 0))
		ft_usleep(1000, philo->main);
	while (main->dead == NO)
	{
		eating(main, philo);
		if (main->is_max_eat == YES)
			break ;
		put_action((t_main *)philo->main, philo->id, SLEEPING);
		sleeping(main);
		put_action((t_main *)philo->main, philo->id, THINKING);
	}
	return (NULL);
}

void	generate(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n_philo)
	{
		if (pthread_create(&main->philo[i].th_id, NULL, routine,
			(void *)&main->philo[i]))
			ft_error(MUTEX_ERROR);
		main->philo[i].last_eat = get_time_ms();
	}
	check_death(main);
	i = -1;
	while (++i < main->n_philo)
		if (pthread_join(main->philo[i].th_id, NULL))
			ft_error(MUTEX_ERROR);
	end_philo(main);
}
