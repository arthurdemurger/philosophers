/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:47:07 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 22:24:26 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	check_death(t_main *main)
{
	int	i;

	while (main->is_max_eat == NO)
	{
		i = -1;
		while (++i < main->n_philo && main->dead == NO)
		{
			pthread_mutex_lock(&main->eating);
			if (get_time_ms() - main->philo[i].last_eat >= main->t_die)
			{
				put_action(main, main->philo[i].id, DIED);
				main->dead = YES;
			}
			pthread_mutex_unlock(&main->eating);
			ft_usleep(100, main);
		}
		if (main->dead)
			break ;
		i = 0;
		while (main->n_max_eat >= 1 && i < main->n_philo
			&& main->philo[i].n_eat >= main->n_max_eat)
			i++;
		if (i == main->n_philo)
			main->is_max_eat = YES;
	}
}

void	init_mutex(t_main *main)
{
	int	i;

	i = -1;
	main->forks = malloc (sizeof(t_mutex) * main->n_philo);
	if (!main->forks)
		ft_error(MALLOC_ERROR);
	while (++i < main->n_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL))
			ft_error(MUTEX_ERROR);
	}
	if (pthread_mutex_init(&main->eating, NULL)
		|| pthread_mutex_init(&main->writing, NULL))
		ft_error(MUTEX_ERROR);
}

void	init_philo(t_main *main)
{
	int		i;

	i = -1;
	main->philo = malloc (sizeof(t_philo) * main->n_philo);
	if (!main->philo)
		ft_error(MALLOC_ERROR);
	i = -1;
	while (++i < main->n_philo)
	{
		main->philo->n_eat = 0;
		main->philo->id = i;
		main->philo[i].l_fk = main->forks[i];
		main->philo[i].r_fk = main->forks[(i + 1) % main->n_philo];
		main->philo[i].last_eat = 0;
		main->philo[i].main = main;
	}
}

void	check_init(int ac, char **av, t_main *main)
{
	if (ac != 5 && ac != 6)
		ft_error(ARGUMENT_ERROR);
	main->dead = NO;
	main->n_max_eat = -1;
	main->is_max_eat = NO;
	main->n_philo = ft_atoi(av[1]);
	main->t_die = ft_atoi(av[2]);
	main->t_eat = ft_atoi(av[3]);
	main->t_sleep = ft_atoi(av[4]);
	main->t_start = get_time_ms();
	if (av[5])
	{
		main->n_max_eat = ft_atoi(av[5]);
		if (main->n_max_eat < 1)
			ft_error("Philosophers must eat at least once.");
	}
	if (main->n_philo <= 1)
		ft_error("There must be at least one philosopher.");
	if (main->t_die < 0 || main->t_sleep < 0
		|| main->t_eat < 0)
		ft_error(WRONG_TIME);
	init_mutex(main);
	init_philo(main);
}
