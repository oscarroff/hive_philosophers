/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:15:38 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/23 14:46:17 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_sleep(t_philo *p, t_data *v)
{
	if (what_you_doing("sleeping", p, v) == ERROR)
		return (ft_error("what_you_doing() fail"));
	if (ft_usleep(v->sleep, &v->end) == ERROR)
		return (ft_error("ft_usleep() fail"));
	if (v->end == true)
		return (SUCCESS);
	if (what_you_doing("thinking", p, v) == ERROR)
		return (ft_error("what_you_doing() fail"));
	return (SUCCESS);
}

int	go_think(t_data *v)
{
	if (ft_usleep(v->think, &v->end) == ERROR)
		return (ft_error("ft_usleep() fail"));
	return (SUCCESS);
}

int	what_you_doing(char *s, t_philo *p, t_data *v)
{
	uint32_t	time;

	if (time_fetch(&time, v->start) == ERROR)
		return (ft_error("time_fetch() fail"));
	if (s[1] == EATING)
	{
		v->ate[p->x - 1] = time;
		v->eating[p->x -1] = true;
	}
	if (s[1] == SLEEPING)
		v->eating[p->x -1] = false;
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail"));
	if (v->end == false)
		printf("%u %u is %s\n", time, p->x, s);
	if (pthread_mutex_unlock(&v->m))
		return (ft_error("pthread_mutex_unlock() fail"));
	return (SUCCESS);
}
