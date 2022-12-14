/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:43:51 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/14 17:59:09 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start(t_main *main)
{
	int	i;

	i = -1;
	main->t_start = get_time_ms();
	while (++i < main->n_phi)
	{
		main->phi[i].last_eat = main->t_start;
		main->phi[i].status = THINK;
		if (pthread_create(&main->phi[i].th_id, NULL, routine, &main->phi[i]))
			ft_error(main, PTHREAD_ERROR);
	}
	check_end(main);
	i = -1;
	while (++i < main->n_phi)
		if (pthread_join(main->phi[i].th_id, NULL))
			ft_error(main, PTHREAD_ERROR);
}

int	main(int ac, char **av)
{
	t_main	main;

	init(ac, av, &main);
	start(&main);
	end_philo(&main);
}
