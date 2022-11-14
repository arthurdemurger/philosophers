/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:00:55 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 15:08:26 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ft_atoi(char *str)
{
	long long	sum;
	int			sign;
	int			i;
	int			size;

	size = 0;
	sum = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++size)
		sum = sum * 10 + str[i++] - 48;
	sum *= sign;
	if ((str[i] != '\0' && !ft_isdigit(str[i]))
		|| (i == 1 && sum == 0 && str[0] != '0')
		|| size > 10 || sum > 2147483647 || sum < -2147483648)
		ft_error(NUMBER_TOO_BIG);
	return (sum);
}