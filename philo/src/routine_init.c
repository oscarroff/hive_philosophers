/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:48 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 10:33:11 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	num_fetch(t_philo *p, t_data *v);
static int	wait_turn(t_philo *p, t_data *v);

int	philo_init(t_philo *p, t_data *v)
{
	if (!num_fetch(p, v))
		return (ft_error("philo_init() fail", NULL));
	p->meals = 0;
	p->fork_l = &v->f[p->x - 1];
	p->lock_l = &v->flock[p->x - 1];
	if (p->x == v->n)
	{
		p->fork_r = &v->f[0];
		p->lock_r = &v->flock[0];
	}
	else
	{
		p->fork_r = &v->f[p->x];
		p->lock_r = &v->flock[p->x];
	}
	if (atomic_time_fetch(&v->ate[p->x - 1], v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (wait_turn(p, v) == ERROR)
		return (ft_error("wait_turn() fail", NULL));
	return (SUCCESS);
}

static int	num_fetch(t_philo *p, t_data *v)
{
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	p->x = v->i++;
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}

static int	wait_turn(t_philo *p, t_data *v)
{
	if (p->x % 2 == ODD && p->x != v->n)
		return (SUCCESS);
	else if (p->x % 2 == EVEN)
	{
		if (ft_usleep(v->eat * 0.8, &v->end) == ERROR)
			return (ft_error("ft_usleep() fail", NULL));
		return (SUCCESS);
	}
	else
	{
		if (ft_usleep(v->eat * 1.6, &v->end) == ERROR)
			return (ft_error("ft_usleep() fail", NULL));
		return (SUCCESS);
	}
}
