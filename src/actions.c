/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:05:52 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/15 11:15:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_lock(&main->fork[phi->l_fk]))
		ft_error(main, MUTEX_ERROR);
	put_action(main, phi->id, FORK);
	if (pthread_mutex_lock(&main->fork[phi->r_fk]))
		ft_error(main, MUTEX_ERROR);
	put_action(main, phi->id, FORK);
}

void	unlock_forks(t_main *main, t_phi *phi)
{
	if (pthread_mutex_unlock(&main->fork[phi->l_fk]))
		ft_error(main, MUTEX_ERROR);
	if (pthread_mutex_unlock(&main->fork[phi->r_fk]))
		ft_error(main, MUTEX_ERROR);
}

void	thinking(t_main *main, int phi_id)
{
	put_action(main, phi_id, THINKING);
	main->phi[phi_id].status = THINK;
}

void	sleeping(t_main *main, int phi_id)
{
	put_action(main, phi_id, SLEEPING);
	main->phi[phi_id].status = SLEEP;
	ft_usleep(main, main->t_sleep);
}

void	eating(t_main *main, t_phi *phi)
{
	lock_forks(main, phi);
	put_action(main, phi->id, EATING);
	phi->status = EAT;
	if (pthread_mutex_lock(&main->eat))
		ft_error(main, MUTEX_ERROR);
	phi->n_eat++;
	if (main->max_eat != -1 && phi->n_eat == main->max_eat)
		main->nb_phi_full++;
	if (pthread_mutex_unlock(&main->eat))
		ft_error(main, MUTEX_ERROR);
	phi->last_eat = get_time_ms();
	ft_usleep(main, main->t_eat);
	unlock_forks(main, phi);
}
