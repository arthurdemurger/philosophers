/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:07:00 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 19:34:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	put_action(t_philo *philo, char *type)
{
	if (pthread_mutex_lock(philo->main->writing))
		ft_error(MUTEX_ERROR);
	if (philo->main->dead == NO)
		ft_printf("%lu %d %s\n", get_time_ms() - philo->main->t_start, philo->id, type);
	if (pthread_mutex_unlock(philo->main->writing));
		ft_error(MUTEX_ERROR);
}

long long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t.tv_sec * 1000) + t.tv_usec) / 1000);
}
