/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutlery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:43:01 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/23 14:44:41 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(atomic_bool *fork, pthread_mutex_t *lock, \
t_philo *p, t_data *v)
{
	uint32_t	time;

	time = 0;
	if (pthread_mutex_lock(lock))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	*fork = true;
	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	if (v->end == false)
		printf("%u %u has taken a fork\n", time, p->x);
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}

int	return_cutlery(t_philo *p, t_data *v)
{
	(void)v;
	*p->fork_l = false;
	*p->fork_r = false;
	if (pthread_mutex_unlock(p->lock_l) || pthread_mutex_unlock(p->lock_r))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}
