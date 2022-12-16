/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:39 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/16 01:08:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

/*
** Libraries
*/

# include <pthread.h>
# include <stdatomic.h>
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
# define ARGUMENT_ERR "philo error : wrong number of arguments."
# define NUMBER_TOO_BIG "philo error : the number entered is too big."
# define WRONG_TIME_ERR "philo error : time not valid."
# define MALLOC_ERR "philo error : there was a problem in a malloc."
# define MUTEX_ERR "philo error : there was a problem in a mutex."
# define PTHREAD_ERR "philo error : there was a problem in a thread."
# define NB_PHI_ERR "philo error : incorrect number of philos."
# define EAT_ERR "philo error : philos cannot eat a negative number of times."
# define NOT_DIGIT_ERR "philo error : only enter numbers."

/* Others */
# define YES 1
# define NO 0
# define MIN_EAT_0 0

/* Actions */
# define FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

/* Status */
# define EAT 0
# define THINK 1
# define SLEEP 2

/*
** Structures
*/

typedef pthread_mutex_t	t_mutex;

typedef struct s_phi
{
	int				status;
	int				id;
	int				n_eat;
	long			last_eat;
	int				l_fk;
	int				r_fk;
	struct s_main	*main;
	pthread_t		th_id;
}	t_phi;

typedef struct s_main
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_phi;
	int				max_eat;
	int				init;
	atomic_int		is_dead;
	int				is_max_eat;
	int				nb_phi_full;
	long			t_start;
	t_phi			*phi;
	t_mutex			*fork;
	t_mutex			write;
	t_mutex			eat;
	t_mutex			status;
	t_mutex			full;
}	t_main;

/*
** Functions
*/

/* Main */
int			init(int ac, char **av, t_main *main);
void		*routine(void *arg);
void		end_philo(t_main *main);

/* Routine */
void		check_end(t_main *main);

/* Actions */
void		eating(t_main *main, t_phi *phi);
void		sleeping(t_main *main, t_phi *phi, int phi_id);
void		unlock_forks(t_main *main, t_phi *phi);
void		lock_forks(t_main *main, t_phi *phi);
void		thinking(t_main *main, t_phi *phi, int phi_id);
void		change_status(t_main * main, t_phi *phi, int status);

/* Error management */
void		ft_error(t_main *main, char *type);

/* Utils */
int			ft_atoi(char *s);
void		ft_putendl_fd(char *s, int fd);
void		ft_usleep(t_main *main, int time);
long		get_time_ms(void);
void		put_action(t_main *main, int philo_id, char *type);
void		mutex_lock(t_main *main, t_mutex *mutex);
void		mutex_unlock(t_main *main, t_mutex *mutex);

#endif
