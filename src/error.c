/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:52:25 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 11:14:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_error(char *type)
{
	write (STDERR_FILENO, "Error\n", 6);
	ft_putendl_fd(type, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
