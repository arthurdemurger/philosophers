/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:54:22 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 11:22:03 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

static int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
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
	while (str[i] && ft_isdigit(str[i]))
	{
		sum = sum * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		ft_error(NOT_DIGIT_ERROR);
	return (sum);
}
