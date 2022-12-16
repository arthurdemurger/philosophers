/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:52:25 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/16 15:32:31 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_main *main)
{
	int	i;

	i = -1;
	if (main)
	{
		while (++i < main->n_phi)
			main->phi[i].main = NULL;
		free(main->phi);
	}
}

void	destroy_mutex(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n_phi)
		if (pthread_mutex_destroy(&main->fork[i]))
			ft_error(main, MUTEX_ERR);
	if (pthread_mutex_destroy(&main->eat))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_destroy(&main->write))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_destroy(&main->status))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_destroy(&main->full))
		ft_error(main, MUTEX_ERR);
}

void	end_philo(t_main *main)
{
	if (main->is_max_eat)
		printf("all philos have eaten %d times\n", main->max_eat);
	if (main->init == YES)
	{
		destroy_mutex(main);
		if (main->phi)
			free_all(main);
	}
	exit(EXIT_SUCCESS);
}

void	ft_error(t_main *main, char *type)
{
	ft_putendl_fd(type, STDERR_FILENO);
	free_all(main);
	exit(EXIT_FAILURE);
}
