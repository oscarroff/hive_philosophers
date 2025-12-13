/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:15:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/13 13:04:57 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	what_you_doing(char *s, t_philo *p);
static int	take_cutlery(t_philo *p, t_vars *v);
static int	return_cutlery(t_philo *p, t_vars *v);

int	go_eat(t_philo *p, t_vars *v)
{
	int				flag;

	flag = take_cutlery(p, v);
	if (flag != SUCCESS)
		return (flag);
	if (!what_you_doing("eating", p))
		return (ERROR);
	usleep(v->eat);
	if (!what_you_doing("savouring", p))
		return (ERROR);
	if (v->end == true)
		return (FAIL);
	p->meals++;
	if (return_cutlery(p, v) != SUCCESS)
		return (ERROR);
	if (!what_you_doing("sleeping", p))
		return (ERROR);
	usleep(v->sleep);
	if (v->end == true)
		return (FAIL);
	if (!what_you_doing("thinking", p))
		return (ERROR);
	return (SUCCESS);
}

static int	what_you_doing(char *s, t_philo *p)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAIL);
	if (s[2] == SAVOURING)
	{
		p->ate_s = time.tv_sec;
		p->ate_u = time.tv_usec;
	}
	else
		printf("%ld.%06u %u is %s\n", time.tv_sec, time.tv_usec, p->x, s);
	return (SUCCESS);
}

static int	take_cutlery(t_philo *p, t_vars *v)
{
	struct timeval	t;
	int				flag;

	if (pthread_mutex_lock(&v->m))
		return (ERROR);
	if (gettimeofday(&t, NULL) == -1)
		return (ERROR);
	if (*p->f1 == false && *p->f2 == false)
	{
		*p->f1 = true;
		printf("%ld.%06u %u has taken a fork\n", t.tv_sec, t.tv_usec, p->x);
		*p->f2 = true;
		printf("%ld.%06u %u has taken a fork\n", t.tv_sec, t.tv_usec, p->x);
		flag = SUCCESS;
	}
	else
		flag = FAIL;
	if (pthread_mutex_unlock(&v->m))
		return (ERROR);
	return (flag);
}

static int	return_cutlery(t_philo *p, t_vars *v)
{
	struct timeval	time;
	int				flag;

	if (pthread_mutex_lock(&v->m))
		return (ERROR);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	if (*p->f1 == true && *p->f2 == true)
	{
		*p->f1 = false;
		*p->f2 = false;
		flag = SUCCESS;
	}
	else
		flag = ERROR;
	if (pthread_mutex_unlock(&v->m))
		return (ERROR);
	return (flag);
}
