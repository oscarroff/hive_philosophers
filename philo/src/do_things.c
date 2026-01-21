/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:15:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:22:20 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	what_you_doing(char *s, t_philo *p, t_data *v);
static int	take_cutlery_odd(t_philo *p, t_data *v);
static int	take_cutlery_even(t_philo *p, t_data *v);
static int	return_cutlery(t_philo *p, t_data *v);

int	go_eat(t_philo *p, t_data *v)
{
	int	flag;

	flag = 0;
	if (p->x % 2 == ODD)
		flag = take_cutlery_odd(p, v);
	else if (p->x % 2 == EVEN)
		flag = take_cutlery_even(p, v);
	if (flag != SUCCESS)
		return (flag);
	if (!what_you_doing("eating", p, v))
		return (ERROR);
	usleep(v->eat);
	if (return_cutlery(p, v) != SUCCESS)
		return (ERROR);
	if (v->end == true)
		return (FAIL);
	if (!what_you_doing("sleeping", p, v))
		return (ERROR);
	usleep(v->sleep);
	if (v->end == true)
		return (FAIL);
	if (!what_you_doing("thinking", p, v))
		return (ERROR);
	return (SUCCESS);
}

static int	what_you_doing(char *s, t_philo *p, t_data *v)
{
	uint32_t	time;

	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (s[1] == SLEEPING)
	{
		p->ate = time;
		p->meals++;
	}
	if (v->end == false)
	{
		if (pthread_mutex_lock(&v->m))
			return (FAIL);
		printf("%u %u is %s\n", time, p->x, s);
		if (pthread_mutex_unlock(&v->m))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	take_cutlery_odd(t_philo *p, t_data *v)
{
	uint32_t	time;
	int			flag;

	while (*p->fork_r == true && v->end == false)
		ft_usleep(1);
	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (*p->fork_r == false && v->end == false)
	{
		if (pthread_mutex_lock(&p->lock_r))
			return (ERROR);
		*p->fork_r = true;
		printf("%u %u has taken a fork\n", time, p->x);
		if (pthread_mutex_unlock(&p->lock_r))
			return (ERROR);
		if (pthread_mutex_lock(&p->lock_l))
			return (ERROR);
		*p->fork_r = true;
		printf("%u %u has taken a fork\n", time, p->x);
		if (pthread_mutex_unlock(&p->lock_l))
			return (ERROR);
		flag = SUCCESS;
	}
	else
		flag = FAIL;
	return (flag);
}

static int	take_cutlery_even(t_philo *p, t_data *v)
{
	uint32_t	time;
	int			flag;

	while (*p->fork_l == true && v->end == false)
		ft_usleep(1);
	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	if (*p->fork_l == false && v->end == false)
	{
		if (pthread_mutex_lock(&p->lock_l))
			return (ERROR);
		*p->fork_l = true;
		printf("%u %u has taken a fork\n", time, p->x);
		if (pthread_mutex_unlock(&p->lock_l))
			return (ERROR);
		if (pthread_mutex_lock(&p->lock_r))
			return (ERROR);
		*p->fork_r = true;
		printf("%u %u has taken a fork\n", time, p->x);
		if (pthread_mutex_unlock(&p->lock_r))
			return (ERROR);
		flag = SUCCESS;
	}
	else
		flag = FAIL;
	return (flag);
}

static int	return_cutlery(t_philo *p, t_data *v)
{
	int	flag;

	(void)v;
	if (*p->fork_l == true && *p->fork_r == true)
	{
		*p->fork_l = false;
		*p->fork_r = false;
		flag = SUCCESS;
	}
	else
		flag = ERROR;
	return (flag);
}
