/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:04 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:09:17 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_and_forks_init(t_data *v)
{
	uint32_t	i;

	v->t = malloc(sizeof(pthread_t) * (v->n + 1));
	v->f = malloc(sizeof(atomic_bool) * v->n);
	v->ate = malloc(sizeof(uint32_t) * v->n);
	v->dead = malloc(sizeof(atomic_bool) * v->n);
	v->done = malloc(sizeof(atomic_bool) * v->n);
	if (!v->t || !v->f || !v->ate || !v->dead || !v->done)
		return (ft_error("malloc() fail", v));
	i = 0;
	while (i < v->n)
	{
		memset(&v->t[i], 0, sizeof(pthread_t));
		v->f[i] = false;
		v->ate[i] = 0;
		v->dead[i] = false;
		v->done[i] = false;
		i++;
	}
	return (true);
}

int	threads_run(t_data *v)
{
	uint32_t	i;

	if (time_init(&v->start) == ERROR)
		return (ft_error("time_init() fail", NULL));
	if (pthread_create(&v->t[0], NULL, monitor, v))
		return (ft_error("pthread_create() fail", v));
	if (v->n == 1)
	{
		if (pthread_create(&v->t[1], NULL, philo_lonely, v))
			return (ft_error("pthread_create() fail", v));
		return (true);
	}
	i = 1;
	while (i < v->n + 1)
	{
		if (i % 2 == ODD)
			if (pthread_create(&v->t[i], NULL, philo_odd, v))
				return (ft_error("pthread_create() fail", v));
		if (i % 2 == EVEN)
			if (pthread_create(&v->t[i], NULL, philo_even, v))
				return (ft_error("pthread_create() fail", v));
		i++;
	}
	return (true);
}

int	threads_join(t_data *v)
{
	void		*return_val;
	long		exit_code;
	uint32_t	i;

	i = 1;
	while (i < v->n + 1)
	{
		if (pthread_join(v->t[i], &return_val))
			return (ft_error("pthread_join() fail", v));
		exit_code = (long)return_val;
		if (exit_code != 0)
		{
			printf("%u error: %ld\n", i, exit_code);
			return (ft_error("thread fail", v));
		}
		i++;
	}
	if (pthread_join(v->t[0], &return_val))
		return (ft_error("pthread_join() fail", v));
	exit_code = (long)return_val;
	if (exit_code != 0)
	{
		printf("%u error: %ld\n", 0, exit_code);
		return (ft_error("thread fail", v));
	}
	return (true);
}
