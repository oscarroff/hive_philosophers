/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:04 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 16:57:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	threads_and_forks_init(t_data *v)
{
	uint32_t	i;

	v->t = malloc(sizeof(pthread_t) * v->n + 1);
	v->f = malloc(sizeof(atomic_bool) * v->n);
	v->ate = malloc(sizeof(uint32_t) * v->n);
	v->dead = malloc(sizeof(atomic_bool) * v->n);
	if (!v->t || !v->f)
	{
		ft_error("malloc() fail", v);
		philo_main_exit(v);
		return (false);
	}
	i = 0;
	while (i < v->n)
	{
		v->f[i] = false;
		v->ate[i] = 0;
		v->dead[i] = false;
		i++;
	}
	return (true);
}

bool	threads_run(t_data *v)
{
	uint32_t	i;

	if (time_init(&v->start) == ERROR)
	{
		ft_error("time_init() fail", NULL);
		return (false);
	}
	if (pthread_create(&v->t[0], NULL, monitor, v))
		{
			ft_error("pthread_create() fail", v);
			return (false);
		}
	i = 1;
	while (i < v->n + 1)
	{
		if (pthread_create(&v->t[i], NULL, philosophise, v))
		{
			ft_error("pthread_create() fail", v);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	threads_join(t_data *v)
{
	void		*return_val;
	long		exit_code;
	uint32_t	i;

	i = 0;
	while (i < v->n + 1)
	{
		if (pthread_join(v->t[i], &return_val))
		{
			ft_error("pthread_join() fail", v);
			return (false);
		}
		exit_code = (long)return_val;
		if (exit_code != 0)
		{
			printf("%u error: %ld\n", i, exit_code);
			ft_error("thread fail", v);
			return (false);
		}
		i++;
	}
	return (true);
}
