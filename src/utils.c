/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:07:00 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 22:33:27 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	ft_usleep(long long time, t_main *main)
{
	long long tmp;

	tmp = get_time_ms();
	while (main->dead == NO)
	{
		if (get_time_ms() - tmp >= time)
			break ;
	}
}

void	put_action(t_main *main, int philo_id, char *type)
{
	if (pthread_mutex_lock(&main->writing))
		ft_error(MUTEX_ERROR);
	if (main->dead == NO)
		printf("%lld %d %s\n", get_time_ms() - main->t_start, philo_id + 1, type);
	if (pthread_mutex_unlock(&main->writing))
		ft_error(MUTEX_ERROR);
}

long long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
