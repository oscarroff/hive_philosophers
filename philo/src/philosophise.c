/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:48 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/13 13:03:18 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_init(t_philo *p, t_vars *v);
static int	num_fetch(t_philo *p, t_vars *v);
static bool	did_you_starve(t_philo *p, t_vars *v);

void	*philosophise(void *data)
{
	t_vars			*v;
	t_philo			p;
	int				flag;

	v = data;
	if (!philo_init(&p, v))
		return (0);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0)
			|| did_you_starve(&p, v))
			return (0);
		if (v->end == false && p.state == 't'
			&& *p.f1 == false && *p.f2 == false)
		{
			flag = go_eat(&p, v);
			if (flag == FAIL)
				return (0);
		}
	}
	return (0);
}

static bool	philo_init(t_philo *p, t_vars *v)
{
	struct timeval	time;

	if (!num_fetch(p, v))
		return (false);
	if (gettimeofday(&time, NULL) == -1)
		return (false);
	p->ate_s = time.tv_sec;
	p->ate_u = time.tv_usec;
	p->meals = 0;
	p->state = 't';
	p->f1 = &v->f[p->x - 1];
	if (p->x == v->n)
		p->f2 = &v->f[0];
	else
		p->f2 = &v->f[p->x];
	return (true);
}

static int	num_fetch(t_philo *p, t_vars *v)
{
	if (pthread_mutex_lock(&v->m))
		return (FAIL);
	p->x = v->i++;
	if (pthread_mutex_unlock(&v->m))
		return (FAIL);
	return (SUCCESS);
}

static bool	did_you_starve(t_philo *p, t_vars *v)
{
	struct timeval	time;
	long long		elapsed;

	if (gettimeofday(&time, NULL) == -1)
		return (false);
	elapsed = ((time.tv_sec - p->ate_s) * USEC_PER_SEC)
		+ (time.tv_usec - p->ate_u);
	if (elapsed > v->die)
	{
		printf("%ld.%06u %u died\n", time.tv_sec, time.tv_usec, p->x);
		v->end = true;
		return (true);
	}
	return (false);
}
