/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:41:59 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 12:07:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	go_eat_odd(t_philo *p, t_data *v);
static int	take_cutlery_odd(t_philo *p, t_data *v);

void	*philo_odd(void *data)
{
	t_data	*v;
	t_philo	p;

	v = data;
	if (!philo_init(&p, v))
		return ((void *)-1);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0))
		{
			v->done[p.x - 1] = true;
			return (NULL);
		}
		if (go_eat_odd(&p, v) == ERROR)
			return ((void *)-1);
		if (v->end == false)
			if (go_sleep(&p, v) == ERROR)
				return ((void *)-1);
		if (v->think > 0 && v->end == false)
			if (go_think(v) == ERROR)
				return ((void *)-1);
	}
}

static int	go_eat_odd(t_philo *p, t_data *v)
{
	if (take_cutlery_odd(p, v) == ERROR)
		return (ft_error("take_cutlery_odd() fail"));
	if (what_you_doing("eating", p, v) == ERROR)
		return (ft_error("what_you_doing() fail"));
	if (ft_usleep(v->eat, &v->end) == ERROR)
		return (ft_error("ft_usleep() fail"));
	if (return_cutlery(p, v) == ERROR)
		return (ft_error("return_cutlery() fail"));
	return (SUCCESS);
}

static int	take_cutlery_odd(t_philo *p, t_data *v)
{
	if (take_fork(p->fork_r, p->lock_r, p, v) == ERROR)
		return (ft_error("take_fork() fail"));
	if (take_fork(p->fork_l, p->lock_l, p, v) == ERROR)
		return (ft_error("take_fork() fail"));
	return (SUCCESS);
}
