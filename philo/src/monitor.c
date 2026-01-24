/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:47:46 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 12:16:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_status(t_data *v);
static int	monitor_exit(t_data *v, uint32_t time, uint32_t i);

void	*monitor(void *data)
{
	t_data	*v;
	int		flag;

	v = data;
	flag = SUCCESS;
	while (flag == SUCCESS)
		flag = check_status(v);
	if (flag == ERROR)
		return ((void *)-1);
	else
		return (NULL);
}

static int	check_status(t_data *v)
{
	uint32_t	time;
	uint32_t	i;
	bool		done;

	time = 0;
	i = 0;
	done = false;
	while (i < v->n)
	{
		if (v->done[i] == true)
			done = true;
		if (time_fetch(&time, v->start) == ERROR)
			return (ft_error("time_fetch() fail", NULL));
		if (v->done[i] == false
			&& time >= v->ate[i] + v->die)
			return (monitor_exit(v, time, i));
		if (usleep(50) == ERROR)
			return (ft_error("usleep() fail", NULL));
		i++;
	}
	if (done == true)
		return (DONE);
	return (SUCCESS);
}

static int	monitor_exit(t_data *v, uint32_t time, uint32_t i)
{
	if (pthread_mutex_lock(&v->m))
		return (ft_error("pthread_mutex_lock() fail", NULL));
	v->end = true;
	printf("%u %u died\n", time, i + 1);
	pthread_mutex_unlock(&v->m);
	return (FAIL);
}
