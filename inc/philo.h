/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:39 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/08 13:07:04 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H

# define PHILO_H

/*
** Libraries
*/

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

/*
** Define constants
*/

/*
** Structures
*/

typedef struct s_philo
{

}	t_philo;

typedef struct s_main
{
	int	nb_philo;
	int	time_eat;
	int	time_die;
	int	time_sleep;
	int	nb_must_eat;
}	t_main;


# endif