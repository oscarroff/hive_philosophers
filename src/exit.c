/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 10:58:44 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 11:55:03 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_it_all(t_data *v);

int	philo_init_exit(t_data *v)
{
	uint32_t	i;

	if (pthread_mutex_destroy(&v->m))
		ft_error("pthread_mutex_destroy() fail");
	i = 0;
	if (v->err_i > 0)
	{
		while (i < v->err_i)
			if (pthread_mutex_destroy(&v->flock[i++]))
				ft_error("pthread_mutex_destroy() fail");
	}
	free_it_all(v);
	return (ERROR);
}

int	philo_threads_exit(t_data *v)
{
	uint32_t	i;

	if (pthread_mutex_destroy(&v->m))
		ft_error("pthread_mutex_destroy() fail");
	i = 0;
	while (i < v->n)
		if (pthread_mutex_destroy(&v->flock[i++]))
			ft_error("pthread_mutex_destroy() fail");
	i = 0;
	if (v->err_i > 0)
		if (threads_join(v) == ERROR)
			ft_error("threads_join() fail");
	free_it_all(v);
	return (ERROR);
}

int	philo_main_exit(t_data *v)
{
	int			flag;
	uint32_t	i;

	flag = SUCCESS;
	i = 0;
	while (i < v->n)
	{
		if (pthread_mutex_destroy(&v->flock[i++]))
		{
			flag = ERROR;
			ft_error("pthread_mutex_init() fail");
		}
	}
	if (pthread_mutex_destroy(&v->m))
	{
		flag = ERROR;
		ft_error("pthread_mutex_init() fail");
	}
	free_it_all(v);
	return (flag);
}

static void	free_it_all(t_data *v)
{
	if (v->t)
		free(v->t);
	if (v->f)
		free(v->f);
	if (v->flock)
		free(v->flock);
	if (v->ate)
		free(v->ate);
	if (v->eating)
		free(v->eating);
	if (v->dead)
		free(v->dead);
	if (v->done)
		free(v->done);
}
