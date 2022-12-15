/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:05:52 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/15 16:41:37 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_lock(&main->fork[phi->l_fk]))
		ft_error(main, MUTEX_ERR);
	put_action(main, phi->id, FORK);
	if (pthread_mutex_lock(&main->fork[phi->r_fk]))
		ft_error(main, MUTEX_ERR);
	put_action(main, phi->id, FORK);
}

void	unlock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_unlock(&main->fork[phi->l_fk]))
		ft_error(main, MUTEX_ERR);
	if (pthread_mutex_unlock(&main->fork[phi->r_fk]))
		ft_error(main, MUTEX_ERR);
}

void	thinking(t_main *main, t_phi *phi, int phi_id)
{
	put_action(main, phi_id, THINKING);
	change_status(main, phi, THINK);
}

void	sleeping(t_main *main, t_phi *phi, int phi_id)
{
	put_action(main, phi_id, SLEEPING);
	change_status(main, phi, SLEEP);
	ft_usleep(main, main->t_sleep);
}

void	eating(t_main *main, t_phi *phi)
{
	lock_forks(main, phi);
	put_action(main, phi->id, EATING);
	if (pthread_mutex_lock(&main->eat))
		ft_error(main, MUTEX_ERR);
	change_status(main, phi, EAT);
	phi->n_eat++;
	if (main->max_eat != -1 && phi->n_eat == main->max_eat)
		main->nb_phi_full++;
	phi->last_eat = get_time_ms();
	if (pthread_mutex_unlock(&main->eat))
		ft_error(main, MUTEX_ERR);
	ft_usleep(main, main->t_eat);
	unlock_forks(main, phi);
}
