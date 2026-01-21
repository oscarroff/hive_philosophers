/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:16:11 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:39:36 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_fetch(uint64_t *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() fail", NULL));
	*time = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000);
	return (SUCCESS);
}

int	ft_usleep(uint32_t time)
{
	uint64_t	start;
	uint64_t	current;

	start = 0;
	current = 0;
	if (time_fetch(&start) == ERROR)
		return (ft_error("time_fetch() fail", NULL));
	while (1)
	{
		if (time_fetch(&current) == ERROR)
			return (ft_error("time_fetch() fail", NULL));
		if (start + (uint64_t)time >= current)
			return (SUCCESS);
	}
}
