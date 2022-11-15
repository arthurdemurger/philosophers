/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:32:55 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 22:07:58 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

int	main (int ac, char **av)
{
	t_main		main;

	check_init(ac, av, &main);
	generate(&main);
	return (0);
}
