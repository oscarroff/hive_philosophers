/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:15:38 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:29:29 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	what_you_doing(char *s, t_philo *p, t_data *v);
static int	take_cutlery_odd(t_philo *p, t_data *v);
static int	take_cutlery_even(t_philo *p, t_data *v);
static int	return_cutlery(t_philo *p, t_data *v);

int	go_eat_odd(t_philo *p, t_data *v)
{
	if (take_cutlery_odd(p, v) == ERROR)
		return (ft_error("take_cutlery_odd() fail", NULL));
	if (what_you_doing("eating", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	ft_usleep(v->eat, &v->end);
	if (return_cutlery(p, v) == ERROR)
		return (ft_error("return_cutlery() fail", NULL));
	if (v->end == true)
		return (SUCCESS);
	if (what_you_doing("sleeping", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	ft_usleep(v->sleep, &v->end);
	if (v->end == true)
		return (SUCCESS);
	if (what_you_doing("thinking", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	return (SUCCESS);
}

int	go_eat_even(t_philo *p, t_data *v)
{
	if (take_cutlery_even(p, v) == ERROR)
		return (ft_error("take_cutlery_even() fail", NULL));
	if (what_you_doing("eating", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	ft_usleep(v->eat, &v->end);
	if (return_cutlery(p, v) == ERROR)
		return (ft_error("return_cutlery() fail", NULL));
	if (v->end == true)
		return (SUCCESS);
	if (what_you_doing("sleeping", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	ft_usleep(v->sleep, &v->end);
	if (v->end == true)
		return (SUCCESS);
	if (what_you_doing("thinking", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	return (SUCCESS);
}

static int	what_you_doing(char *s, t_philo *p, t_data *v)
{
	uint32_t	time;

	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (s[1] == EATING)
	{
		v->ate[p->x - 1] = time;
		v->eating[p->x -1] = true;
	}
	if (s[1] == SLEEPING)
	{
		v->eating[p->x -1] = false;
		p->meals++;
	}
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	if (v->end == false)
		printf("%u %u is %s\n", time, p->x, s);
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}

static int	take_cutlery_odd(t_philo *p, t_data *v)
{
	uint32_t	time;

	time = 0;
	if (pthread_mutex_lock(p->lock_r))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	*p->fork_r = true;
	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	if (v->end == false)
		printf("%u %u has taken a fork\n", time, p->x);
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
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
	return (SUCCESS);
}

static int	take_cutlery_even(t_philo *p, t_data *v)
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
	if (pthread_mutex_lock(p->lock_r))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	*p->fork_r = true;
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

static int	return_cutlery(t_philo *p, t_data *v)
{
	(void)v;
	*p->fork_l = false;
	*p->fork_r = false;
	if (pthread_mutex_unlock(p->lock_l) || pthread_mutex_unlock(p->lock_r))
		return (ft_error("pthread_mutex_unlock() fail", NULL));
	return (SUCCESS);
}
