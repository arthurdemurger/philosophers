/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:47:07 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 16:56:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	init_mutex(t_main *main)
{
	// code
}

void	init_pthread(t_main *main)
{
	int	i;

	i = -1;
	while (i++ < main->nb_philo)
		pthread_create(&main->philo->thread_id, NULL, routine, main);
}

void	init_philo(t_main *main)
{
	int		i;

	i = -1;
	main->philo = malloc (sizeof(t_philo) * main->nb_philo);
	main->forks = malloc (sizeof(t_philo) * main->nb_philo);
	if (!main->philo || !main->forks)
		ft_error(MALLOC_ERROR);
	while (++i < main->nb_philo)
		main->forks[i] = i;
	i = -1;
	while (++i < main->nb_philo)
	{
		main->philo[i].id = i;
		main->philo[i].is_dead = NO;
		main->philo[i].l_fk_id = main->forks[i];
		main->philo[i].r_fk_id = main->forks[(i + 1) % main->nb_philo];
		main->philo[i].last_eat = 0;
	}
}

void	check_init(int ac, char **av, t_main *main)
{
	if (ac != 5 && ac != 6)
		ft_error(ARGUMENT_ERROR);
	main->nb_must_eat = -1;
	main->count_eat = NO;
	main->nb_philo = ft_atoi(av[1]);
	main->time_to_die = ft_atoi(av[2]);
	main->time_to_eat = ft_atoi(av[3]);
	main->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		main->nb_must_eat = ft_atoi(av[5]);
		if (main->nb_must_eat < 1)
			ft_error("Philosophers must eat at least once.");
		main->count_eat = YES;
	}
	if (main->nb_philo <= 1)
		ft_error("There must be at least one philosopher.");
	if (main->time_to_die < 0 || main->time_to_sleep < 0
		|| main->time_to_eat < 0)
		ft_error(WRONG_TIME);
	init_philo(main);
	init_pthread(main);
	init_mutex(main);
}
