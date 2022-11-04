/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:32:55 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/04 16:59:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	*routine()
{
	printf("lol\n");
	sleep(3);
	printf("test\n");
	return (NULL);
}

int	main ()
{
	pthread_t	t1;
	pthread_create(&t1, NULL, routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}
