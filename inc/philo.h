/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:39 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/14 16:56:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H

# define PHILO_H

/*
** Libraries
*/

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Define constants
*/

# define ARGUMENT_ERROR "Wrong number of arguments."
# define NUMBER_TOO_BIG "The number entered is too big."
# define WRONG_TIME "Time cannot be negative"
# define MALLOC_ERROR "There was a problem in a malloc"
# define YES 1
# define NO 0

/*
** Structures
*/

typedef struct s_philo
{
	pthread_t	thread_id;
	int			id;
	int			l_fk_id;
	int			r_fk_id;
	int			is_dead;
	long long	last_eat;
}	t_philo;

typedef struct s_main
{
	t_philo	*philo;
	int		*forks;
	int		nb_philo;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		nb_must_eat;
	int		count_eat;
}	t_main;

/*
** Functions
*/

void	check_init(int ac, char **av, t_main *main);
void	ft_error(char *type);
void	routine(t_main *main);

/*
** Utils functions
*/

int		ft_atoi(char *s);
int		ft_isdigit(char c);
void	ft_putendl_fd(char *s, int fd);

# endif