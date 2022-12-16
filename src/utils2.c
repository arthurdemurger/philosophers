/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:58:37 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/16 01:08:02 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mutex_unlock(t_main *main, t_mutex *mutex)
{
	if (pthread_mutex_unlock(mutex))
		ft_error(main, MUTEX_ERR);
}

void	mutex_lock(t_main *main, t_mutex *mutex)
{
	if (pthread_mutex_lock(mutex))
		ft_error(main, MUTEX_ERR);
}
