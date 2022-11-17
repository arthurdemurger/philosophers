/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:05:52 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/17 15:27:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_lock(&main->fork[phi->l_fk]))
		ft_error(MUTEX_ERROR);
	put_action(main, phi->id, FORK);
	if (pthread_mutex_lock(&main->fork[phi->r_fk]))
		ft_error(MUTEX_ERROR);
	put_action(main, phi->id, FORK);
}

void	unlock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_unlock(&main->fork[phi->l_fk]))
		ft_error(MUTEX_ERROR);
	if (pthread_mutex_unlock(&main->fork[phi->r_fk]))
		ft_error(MUTEX_ERROR);
}

void	sleeping(t_main *main, int phi_id)
{
	ft_usleep(main->t_sleep);
	put_action(main, phi_id, SLEEPING);
}

void	eating(t_main *main, t_phi *phi)
{
	lock_forks(main, phi);
	put_action(main, phi->id, EATING);
	if (pthread_mutex_lock(&main->eat))
		ft_error(MUTEX_ERROR);	phi->n_eat++;
	phi->last_eat = get_time_ms();
	if (phi->n_eat == main->max_eat)
		main->nb_phi_full++;
	if (pthread_mutex_unlock(&main->eat))
		ft_error(MUTEX_ERROR);
	ft_usleep(main->t_eat);
	unlock_forks(main, phi);
}
