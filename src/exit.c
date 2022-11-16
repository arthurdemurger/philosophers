/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:52:25 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 15:56:49 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_error(char *type)
{
	write (STDERR_FILENO, "Error\n", 6);
	ft_putendl_fd(type, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_all(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n_phi)
		main->phi[i].main = NULL;
	free(main->phi);
}

void	end_philo(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n_phi)
		if (pthread_mutex_destroy(&main->fork[i]))
			ft_error(MUTEX_ERROR);
	if (pthread_mutex_destroy(&main->eat))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_destroy(&main->write))
		ft_error(MUTEX_ERROR);
	free_all(main);
	exit(EXIT_SUCCESS);
}