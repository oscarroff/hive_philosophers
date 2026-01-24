/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:04 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 11:50:31 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	multi_philo(t_data *v);

int	threads_run(t_data *v)
{
	if (time_init(&v->start) == ERROR)
		return (ft_error("time_init() fail"));
	if (pthread_create(&v->t[0], NULL, monitor, v))
		return (ft_error("pthread_create() fail"));
	if (v->n == 1)
	{
		if (pthread_create(&v->t[1], NULL, philo_lonely, v))
		{
			v->err_i = 1;
			return (ft_error("pthread_create() fail"));
		}
		return (SUCCESS);
	}
	if (multi_philo(v) == ERROR)
		return (ft_error("multi_philo() fail"));
	return (SUCCESS);
}

static int	multi_philo(t_data *v)
{
	uint32_t	i;

	i = 1;
	while (i < v->n + 1)
	{
		if (i % 2 == ODD)
		{
			if (pthread_create(&v->t[i], NULL, philo_odd, v))
			{
				v->err_i = i;
				return (ft_error("pthread_create() fail"));
			}
		}
		if (i % 2 == EVEN)
		{
			if (pthread_create(&v->t[i], NULL, philo_even, v))
			{
				v->err_i = i;
				return (ft_error("pthread_create() fail"));
			}
		}
		i++;
	}
	return (SUCCESS);
}

static int	close_thread(pthread_t *t, uint32_t i, t_data *v)
{
	void		*return_val;
	long		exit_code;

	if (pthread_join(*t, &return_val))
		return (ft_error("pthread_join() fail"));
	exit_code = (long)return_val;
	if (exit_code != 0)
	{
		printf("%u error: %ld\n", i, exit_code);
		return (ft_error("thread ));
	}
	return (SUCCESS);
}

int	threads_join(t_data *v)
{
	uint32_t	n;
	uint32_t	i;
	int			flag;

	flag = SUCCESS;
	if (v->err_i > 0)
		n = v->err_i - 1;
	else
		n = v->n;
	i = 1;
	while (i < n + 1)
	{
		if (close_thread(&v->t[i], i, v) == ERROR)
		{
			flag = ERROR;
			ft_error("close_thread() fail");
		}
		i++;
	}
	if (close_thread(&v->t[0], 0, v) == ERROR)
	{
		flag = ERROR;
		return (ft_error("close_thread() fail"));
	}
	return (flag);
}
