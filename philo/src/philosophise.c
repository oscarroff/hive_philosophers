/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:48 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:30:09 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_init(t_philo *p, t_data *v);
static int	num_fetch(t_philo *p, t_data *v);

static int	philo_lonely_init(t_philo *p, t_data *v)
{
	if (!num_fetch(p, v))
		return (ft_error("philo_init() fail", NULL));
	p->meals = 0;
	p->fork_l = &v->f[0];
	p->lock_l = &v->flock[0];
	if (atomic_time_fetch(&v->ate[p->x - 1], v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	return (SUCCESS);
}

int	go_think(t_data *v)
{
	if (ft_usleep(v->think, &v->end) == ERROR)
		return (ft_error("ft_usleep() fail", NULL));
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

void	*philo_odd(void *data)
{
	t_data	*v;
	t_philo	p;

	v = data;
	if (!philo_init(&p, v))
		return (THREAD_ERROR);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0))
		{
			v->done[p.x - 1] = true;
			return (THREAD_SUCCESS);
		}
		if (go_eat_odd(&p, v) == ERROR)
			return (THREAD_ERROR);
		if (v->end == false)
			if (go_sleep(&p, v) == ERROR)
				return (THREAD_ERROR);
		if (v->think > 0 && v->end == false)
			if (go_think(v) == ERROR)
				return (THREAD_ERROR);
	}
}

void	*philo_even(void *data)
{
	t_data			*v;
	t_philo			p;

	v = data;
	if (!philo_init(&p, v))
		return (THREAD_ERROR);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0))
		{
			v->done[p.x - 1] = true;
			return (THREAD_SUCCESS);
		}
		if (go_eat_even(&p, v) == ERROR)
			return (THREAD_ERROR);
		if (v->end == false)
			if (go_sleep(&p, v) == ERROR)
				return (THREAD_ERROR);
		if (v->think > 0 && v->end == false)
			if (go_think(v) == ERROR)
				return (THREAD_ERROR);
	}
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

static int	philo_init(t_philo *p, t_data *v)
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
