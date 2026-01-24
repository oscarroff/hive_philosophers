/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:16:11 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:33:18 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdatomic.h>

int	time_init(uint32_t *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() fail", NULL));
	*time = (tv.tv_sec * (uint32_t)1000) + (tv.tv_usec / (uint32_t)1000);
	return (SUCCESS);
}

int	time_fetch(uint32_t *time, uint32_t start)
{
	uint32_t	now;

	now = 0;
	if (time_init(&now) == ERROR)
		return (ft_error("time_init() fail", NULL));
	*time = now - start;
	return (SUCCESS);
}

int	atomic_time_fetch(atomic_uint_fast32_t *time, uint32_t start)
{
	uint32_t				now;

	now = 0;
	if (time_init(&now) == ERROR)
		return (ft_error("time_init() fail", NULL));
	*time = now - start;
	return (SUCCESS);
}

int	ft_usleep(uint32_t time, atomic_bool *end)
{
	uint32_t	start;
	uint32_t	current;

	start = 0;
	current = 0;
	if (time_init(&start) == ERROR)
		return (ft_error("time_init() fail", NULL));
	while (1)
	{
		if (time_init(&current) == ERROR)
			return (ft_error("time_init() fail", NULL));
		if (current >= start + time || *end == true)
			return (SUCCESS);
		if (usleep(300) == ERROR)
			return (ft_error("usleep() fail", NULL));
	}
}
