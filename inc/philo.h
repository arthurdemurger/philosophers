/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:39 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/15 21:53:10 by ademurge         ###   ########.fr       */
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

/* DEBUG */

# define ICI printf("ici\n");
# define LEAKS system("leaks philo");

/* Characters */

# define ARGUMENT_ERROR "Wrong number of arguments."
# define NUMBER_TOO_BIG "The number entered is too big."
# define WRONG_TIME "Time cannot be negative"
# define MALLOC_ERROR "There was a problem in a malloc"
# define MUTEX_ERROR "There was a problem in a mutex"
# define YES 1
# define NO 0
# define FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

/*
** Structures
*/

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int					id;
	int					n_eat;
	t_mutex				l_fk;
	long long			last_eat;
	t_mutex				r_fk;
	struct s_main		*main;
	pthread_t			th_id;
}	t_philo;

typedef struct s_main
{
	int					dead;
	t_mutex				eating;
	t_mutex				*forks;
	int					n_max_eat;
	int					is_max_eat;
	int					n_philo;
	t_philo				*philo;
	int					t_eat;
	int					t_die;
	int					t_sleep;
	long long			t_start;
	t_mutex				writing;
}	t_main;

/*
** Functions
*/

void		check_death(t_main *main);
void		check_init(int ac, char **av, t_main *main);
void		end_philo(t_main *main);
void		ft_error(char *type);
void		ft_usleep(long long time, t_main *main);
void		generate(t_main *main);
long long	get_time_ms(void);
void		*routine(void *arg);
void		put_action(t_main *main, int philo_id, char *type);

/*
** Utils functions
*/

int		ft_atoi(char *s);
int		ft_isdigit(char c);
void	ft_putendl_fd(char *s, int fd);

# endif