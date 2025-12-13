/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:04 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/13 13:04:20 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	threads_and_forks_init(t_vars *v)
{
	uint32_t	i;

	v->t = malloc(sizeof(pthread_t) * v->n);
	v->f = malloc(sizeof(atomic_bool) * v->n);
	if (!v->t || !v->f)
	{
		clean_up(v);
		return (false);
	}
	i = 0;
	while (i < v->n)
		v->f[i++] = false;
	return (true);
}

bool	threads_run(t_vars *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_create(&v->t[i], NULL, philosophise, v))
		{
			printf("Error: thread failed\n");
			clean_up(v);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	threads_join(t_vars *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_join(v->t[i], NULL))
		{
			printf("Error: thread join failed\n");
			clean_up(v);
			return (false);
		}
		i++;
	}
	return (true);
}
