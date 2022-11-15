/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:47:30 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 11:23:25 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	end_philo(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->n_philo)
		if (pthread_mutex_destroy(&main->forks[i]))
			ft_error(MUTEX_ERROR);
	free(main->philo);
	free(main->forks);
	if (pthread_mutex_destroy(&main->eating))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_destroy(&main->writing))
		ft_error(MUTEX_ERROR);
	exit(EXIT_SUCCESS);
}

void	ft_error(char *type)
{
	ft_putendl_fd(type, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
