/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:02:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 15:46:15 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_mutex(t_main *main)
{
	int	i;

	main->fork = malloc (sizeof(t_mutex) * main->n_phi);
	if (!main->fork)
		ft_error(MALLOC_ERROR);
	i = -1;
	while (++i < main->n_phi)
		if (pthread_mutex_init(&main->fork[i], NULL))
			ft_error(MUTEX_ERROR);
	if (pthread_mutex_init(&main->write, NULL))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_init(&main->eat, NULL))
		ft_error(MUTEX_ERROR);
}

void	init_philo(t_main *main)
{
	int	i;

	main->phi = malloc (sizeof(t_phi) * main->n_phi);
	if (!main->phi)
		ft_error(MALLOC_ERROR);
	i = -1;
	while (++i < main->n_phi)
	{
		main->phi[i].id = i;
		main->phi[i].last_eat = 0;
		main->phi[i].n_eat = 0;
		main->phi[i].l_fk = i;
		main->phi[i].r_fk = (i + 1) % main->n_phi;
		main->phi[i].main = main;
	}
}

void	init(int ac, char **av, t_main *main)
{
	main->max_eat = -1;
	if (ac != 5 && ac != 6)
		ft_error(ARGUMENT_ERROR);
	main->n_phi = ft_atoi(av[1]);
	main->t_die = ft_atoi(av[2]);
	main->t_eat = ft_atoi(av[3]);
	main->t_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		if (ft_atoi(av[5]) >= 0)
			main->max_eat = ft_atoi(av[5]);
		else
			ft_error(MIN_EAT_ERROR);
	}
	if (main->n_phi < 1)
		ft_error(NB_PHILO_ERROR);
	else if (main->t_die < 0 || main->t_eat < 0 || main->t_sleep < 0)
		ft_error(WRONG_TIME_ERROR);
	main->is_dead = NO;
	main->is_max_eat = NO;
	main->nb_phi_full = 0;
	init_philo(main);
	init_mutex(main);
}
