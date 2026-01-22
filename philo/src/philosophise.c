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
static void	*philo_exit(t_philo *p);

static void	*philo_exit(t_philo *p)
{
	pthread_mutex_destroy(&p->lock_l);
	pthread_mutex_destroy(&p->lock_r);
	return (THREAD_SUCCESS);
}

static int	philo_lonely_init(t_philo *p, t_data *v)
{
	if (!num_fetch(p, v))
		return (ft_error("philo_init() fail", NULL));
	p->meals = 0;
	p->fork_l = &v->f[0];
	if (pthread_mutex_init(&p->lock_l, NULL))
		return (ft_error("pthread_mutex_init() fail", NULL));
	if (time_fetch(&v->ate[p->x - 1], v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
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
			return (philo_exit(&p));
		}
		ft_usleep(300, &v->end);
	}
}

void	*philo_odd(void *data)
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
			return (philo_exit(&p));
		}
		else
			if (go_eat_odd(&p, v) == ERROR)
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
			return (philo_exit(&p));
		}
		else
			if (go_eat_even(&p, v) == ERROR)
				return (THREAD_ERROR);
	}
}

static int	wait_turn(t_philo *p, t_data *v)
{
	if (p->x % 2 == ODD && p->x != v->n && v->n > 1)
		return (SUCCESS);
	else if (p->x % 2 == EVEN)
	{
		if (ft_usleep(v->eat, &v->end) == ERROR)
			return (ft_error("ft_usleep() fail", NULL));
		return (SUCCESS);
	}
	else
	{
		if (ft_usleep(v->eat * 2, &v->end) == ERROR)
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
	if (p->x == v->n)
		p->fork_r = &v->f[0];
	else
		p->fork_r = &v->f[p->x];
	if (pthread_mutex_init(&p->lock_l, NULL))
		return (ft_error("pthread_mutex_init() fail", NULL));
	if (pthread_mutex_init(&p->lock_r, NULL))
	{
		pthread_mutex_destroy(&p->lock_l);
		return (ft_error("pthread_mutex_init() fail", NULL));
	}
	if (time_fetch(&v->ate[p->x - 1], v->start) == ERROR)
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
