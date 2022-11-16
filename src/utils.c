/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:54:22 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 14:30:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(long long time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() < start + time)
		usleep(10);
}

void	put_action(t_main *main, int philo_id, char *type)
{
	if (pthread_mutex_lock(&main->write))
		ft_error(MUTEX_ERROR);
	if (main->is_dead == NO && main->is_max_eat == NO)
		printf("%lld %d %s\n", get_time_ms() - main->t_start, philo_id + 1,
			type);
	if (pthread_mutex_unlock(&main->write))
		ft_error(MUTEX_ERROR);
}

long long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_putendl_fd(char *s, int fd)
{
	while (s && *s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

int	ft_atoi(char *str)
{
	long long	sum;
	int			i;

	sum = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		sum = sum * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		ft_error(NOT_DIGIT_ERROR);
	return (sum);
}
