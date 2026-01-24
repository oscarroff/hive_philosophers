/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:10:20 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 11:22:27 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "messages.h"

static void	vars_init(t_data *v);
static int	malloc_helper(t_data *v);

int	parse_args(t_data *v, char **argv)
{
	vars_init(v);
	if (!ft_atoui(&v->n, argv[1]) || v->n == 0
		|| !ft_atoui(&v->die, argv[2])
		|| !ft_atoui(&v->eat, argv[3])
		|| !ft_atoui(&v->sleep, argv[4]))
	{
		printf("%s\n", MSG_VALID);
		printf("%s", MSG_PROMPT);
		return (FAIL);
	}
	if (argv[5])
	{
		if (!ft_atoui(&v->fed, argv[5]) || v->fed == 0)
		{
			printf("%s\n", MSG_VALID);
			printf("%s", MSG_PROMPT);
			return (FAIL);
		}
	}
	if (v->sleep <= v->eat && v->n % 2 == ODD)
		v->think = v->eat - v->sleep + 1;
	if (pthread_mutex_init(&v->m, NULL))
		ft_error("pthread_mutex_init() fail", NULL);
	return (SUCCESS);
}

static void	vars_init(t_data *v)
{
	v->n = 0;
	v->die = 0;
	v->eat = 0;
	v->sleep = 0;
	v->think = 0;
	v->fed = 0;
	v->start = 0;
	v->i = 1;
	v->f = NULL;
	v->end = false;
	v->t = NULL;
	v->err_i = 0;
}

int	init(t_data *v)
{
	uint32_t	i;

	if (malloc_helper(v) == ERROR)
	{
		philo_init_exit(v);
		return (ft_error("malloc_helper() fail", v));
	}
	i = 0;
	while (i < v->n)
	{
		memset(&v->t[i], 0, sizeof(pthread_t));
		v->f[i] = false;
		memset(&v->flock[i], 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&v->flock[i], NULL))
		{
			v->err_i = i;
			return (ft_error("pthread_mutex_init() fail", NULL));
		}
		v->ate[i] = 0;
		v->eating[i] = false;
		v->dead[i] = false;
		v->done[i] = false;
		i++;
	}
	return (SUCCESS);
}

static int	malloc_helper(t_data *v)
{
	v->t = malloc(sizeof(pthread_t) * (v->n + 1));
	v->f = malloc(sizeof(atomic_bool) * v->n);
	v->flock = malloc(sizeof(pthread_mutex_t) * v->n);
	v->ate = malloc(sizeof(atomic_uint_fast32_t) * v->n);
	v->eating = malloc(sizeof(atomic_bool) * v->n);
	v->dead = malloc(sizeof(atomic_bool) * v->n);
	v->done = malloc(sizeof(atomic_bool) * v->n);
	if (!v->t || !v->f || !v->flock || !v->ate || !v->dead || !v->done)
		return (ft_error("malloc() fail", v));
	return (SUCCESS);
}
