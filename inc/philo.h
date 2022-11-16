/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:39 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/16 11:44:55 by ademurge         ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

/*
** Define constants
*/

/* Debug */
# define ICI printf("ici\n");
# define LEAKS system("leaks philo");

/* Error management */
# define ARGUMENT_ERROR "Wrong number of arguments."
# define NUMBER_TOO_BIG "The number entered is too big."
# define WRONG_TIME_ERROR "Time cannot be negative."
# define MALLOC_ERROR "There was a problem in a malloc."
# define MUTEX_ERROR "There was a problem in a mutex."
# define NB_PHILO_ERROR "There must be at least one philo."
# define MIN_EAT_ERROR "Philosophers cannot eat a negative number of times."
# define NOT_DIGIT_ERROR "Only enter numbers."
/* Others */
# define YES 1
# define NO 0

/* The different actions */
# define FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

/*
** Structures
*/

typedef pthread_mutex_t	t_mutex;

typedef struct s_phi
{
	int			id;
	int			n_eat;
	long long	last_eat;
	int			l_fk;
	int			r_fk;
	pthread_t	th_id;
}	t_phi;

typedef struct s_main
{
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_phi;
	int			max_eat;
	long long	t_start;
	t_phi		*phi;
	t_mutex		*fork;
}	t_main;

/*
** Functions
*/

/* Main */
void	init(int ac, char **av, t_main *main);


/* Exit management */
void	ft_error(char *type);

/* Utils */
int		ft_atoi(char *s);
void	ft_putendl_fd(char *s, int fd);

# endif