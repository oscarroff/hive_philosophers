/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:47:46 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 16:49:57 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_status(t_data *v)
{
	uint32_t	time;
	uint32_t	i;

	time = 0;
	i = 0;
	while (i < v->n)
	{
		if (time_fetch(&time, v->start) == ERROR)
		{
			ft_error("time_fetch() fail", NULL);
			return (ERROR);
		}
		if (time >= v->ate[i] + v->die)
		{
			if (pthread_mutex_lock(&v->m))
				return (ERROR);
			printf("%u %u died\n", time, i);
			v->end = true;
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	*monitor(void *data)
{
	t_data	*v;
	int		flag;

	v = data;
	flag = SUCCESS;
	// if (!monitor_init(&p, v))
	// 	return (THREAD_ERROR);
	while (flag == SUCCESS)
		flag = check_status(v);
	if (flag == ERROR)
		return (THREAD_ERROR);
	else
		return (THREAD_SUCCESS);
}
