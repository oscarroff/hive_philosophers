/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_lonely.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 10:25:30 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 10:29:39 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_lonely_init(t_philo *p, t_data *v)
{
	p->x = 1;
	p->meals = 0;
	p->fork_l = &v->f[0];
	p->lock_l = &v->flock[0];
	if (atomic_time_fetch(&v->ate[p->x - 1], v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	return (SUCCESS);
}

static int	lonely_meal(t_philo *p, t_data *v)
{
	uint32_t	time;

	time = 0;
	if (pthread_mutex_lock(p->lock_l))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	*p->fork_l = true;
	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	if (v->end == false)
		printf("%u %u has taken a fork\n", time, p->x);
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	while (v->end == false)
		ft_usleep(50, &v->end);
	if (pthread_mutex_unlock(p->lock_l))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}

void	*philo_lonely(void *data)
{
	t_data			*v;
	t_philo			p;

	v = data;
	if (!philo_lonely_init(&p, v))
		return (THREAD_ERROR);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0))
		{
			v->done[p.x - 1] = true;
			return (THREAD_SUCCESS);
		}
		else
		{
			if (lonely_meal(&p, v) == ERROR)
				return (THREAD_ERROR);
		}
	}
}
