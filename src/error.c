/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:47:30 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 14:57:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	ft_error(char *type)
{
	ft_putendl_fd(type, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
