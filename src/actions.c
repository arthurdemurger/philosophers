/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:05:52 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/16 01:08:57 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_main *main, t_phi *phi)
{
	mutex_lock(main, &main->fork[phi->l_fk]);
	put_action(main, phi->id, FORK);
	mutex_lock(main, &main->fork[phi->r_fk]);
	put_action(main, phi->id, FORK);
}

void	unlock_forks(t_main *main, t_phi *phi)
{
	mutex_unlock(main, &main->fork[phi->l_fk]);
	mutex_unlock(main, &main->fork[phi->r_fk]);
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
	mutex_lock(main, &main->eat);
	change_status(main, phi, EAT);
	phi->n_eat++;
	if (main->max_eat != -1 && phi->n_eat == main->max_eat)
	{
		mutex_lock(main, &main->full);
		main->nb_phi_full++;
		mutex_unlock(main, &main->full);
	}
	phi->last_eat = get_time_ms();
	mutex_unlock(main, &main->eat);
	ft_usleep(main, main->t_eat);
	unlock_forks(main, phi);
}
