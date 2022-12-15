/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:54:22 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/15 17:08:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(t_main *main, int time_sleep)
{
	long	start_time;
	long	now_time;

	start_time = get_time_ms();
	while (!main->is_dead)
	{
		now_time = get_time_ms();
		if (now_time - start_time >= time_sleep)
			break ;
		usleep(100);
	}
}

void	put_action(t_main *main, int philo_id, char *type)
{
	mutex_lock(main, main->write);
	if (main->is_dead == NO && main->is_max_eat == NO)
		printf("%ld %d %s\n", get_time_ms() - main->t_start, philo_id + 1,
			type);
	mutex_unlock(main, main->write);
}

long	get_time_ms(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
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
		ft_error(NULL, NOT_DIGIT_ERR);
	return (sum);
}
