/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:51:25 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 19:58:39 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	sleeping(t_main *main, t_philo *philo)
{
	// code
}

void	eating(t_main *main, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fk))
		ft_error(MUTEX_ERROR);
	put_action(philo, FORK);
	if (pthread_mutex_lock(&philo->r_fk))
		ft_error(MUTEX_ERROR);
	put_action(philo, FORK);
	put_action(philo, EATING);
	if (pthread_mutex_lock(&main->eating))
		ft_error(MUTEX_ERROR);
	philo->last_eat = get_time_ms();
	if (++philo->n_eat == main->max_eat)
		// code
	if (pthread_mutex_unlock(&philo->r_fk))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_unlock(&philo->l_fk))
		ft_error(MUTEX_ERROR);
}

void	routine(void *arg)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)arg;
	main = philo->main;
	while (1)
	{
		eating(main, philo);
		if (main->dead == YES)
			break ;
		sleeping(main, philo);
		if (main->dead == YES)
			break ;
		put_action(philo, SLEEPING);
		if (main->dead == YES)
			break ;
		put_action(philo, THINKING);
	}
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
