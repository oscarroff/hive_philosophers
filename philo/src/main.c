/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 14:18:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "philo.h"

void	clean_up(t_vars *v)
{
	if (v->t)
		free(v->t);
	if (v->f)
		free(v->f);
}

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

int	num_fetch(t_philo *p, t_vars *v)
{
	if (pthread_mutex_lock(&v->m))
		return (FAIL);
	p->x = v->i++;
	if (pthread_mutex_unlock(&v->m))
		return (FAIL);
	return (SUCCESS);
}

bool	philo_init(t_philo *p, t_vars *v)
{
	struct timeval	time;

	if (!num_fetch(p, v))
		return (false);
	if (gettimeofday(&time, NULL) == -1)
		return (false);
	p->ate_s = time.tv_sec;
	p->ate_u = time.tv_usec;
	p->meals = 0;
	p->state = 't';
	p->f1 = &v->f[p->x - 1];
	if (p->x == v->n)
		p->f2 = &v->f[0];
	else
		p->f2 = &v->f[p->x];
	return (true);
}

bool	did_you_starve(t_philo *p, t_vars *v)
{
	struct timeval	time;
	long long		elapsed;

	if (gettimeofday(&time, NULL) == -1)
		return (false);
	elapsed = (time.tv_sec - p->ate_s) * 1000000 + (time.tv_usec - p->ate_u);
	if (elapsed > v->die)
	{
		printf("%ld.%u %u died\n", time.tv_sec, time.tv_usec, p->x);
		return (true);
	}
	return (false);
}

int	return_cutlery(t_philo *p, t_vars *v)
{
	struct timeval	time;
	int	flag;

	if (pthread_mutex_lock(&v->m))
		return (ERROR);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	if (*p->f1 == true && *p->f2 == true)
	{
		*p->f1 = false;
		*p->f2 = false;
		flag = SUCCESS;
	}
	else
		flag = ERROR;
	if (pthread_mutex_unlock(&v->m))
		return (ERROR);
	return (flag);
}

int	take_cutlery(t_philo *p, t_vars *v)
{
	struct timeval	time;
	int	flag;

	if (pthread_mutex_lock(&v->m))
		return (ERROR);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	if (*p->f1 == false && *p->f2 == false)
	{
		*p->f1 = true;
		printf("%ld.%u %u has taken a fork\n", time.tv_sec, time.tv_usec, p->x);
		*p->f2 = true;
		printf("%ld.%u %u has taken a fork\n", time.tv_sec, time.tv_usec, p->x);
		flag = SUCCESS;
	}
	else
		flag = FAIL;
	if (pthread_mutex_unlock(&v->m))
		return (ERROR);
	return (flag);
}

int	go_eat(t_philo *p, t_vars *v)
{
	struct timeval	time;
	int				flag;

	flag = take_cutlery(p, v);
	if (flag != SUCCESS)
		return (flag);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	printf("%ld.%u %u is eating\n", time.tv_sec, time.tv_usec, p->x);
	usleep(v->eat);
	if (return_cutlery(p, v) != SUCCESS)
		return (ERROR);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	p->ate_s = time.tv_sec;
	p->ate_u = time.tv_usec;
	printf("%ld.%u %u is sleeping\n", time.tv_sec, time.tv_usec, p->x);
	usleep(v->sleep);
	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	printf("%ld.%u %u is thinking\n", time.tv_sec, time.tv_usec, p->x);
	return (SUCCESS);
}

void	*philosophise(void *data)
{
	t_vars			*v;
	t_philo			p;
	int				flag;

	v = data;
	if (!philo_init(&p, v))
		return (0);
	printf("%ld.%u %u is here\n", p.ate_s, p.ate_u, p.x);
	while (1)
	{
		if (v->end == true || (p.meals >= v->fed && v->fed > 0)
			|| did_you_starve(&p, v))
			return (0);
		if (v->end == false && p.state == 't' && p.f1 == false && p.f2 == false)
		{
			flag = go_eat(&p, v);
			if (flag == FAIL)
				return (0); // I would like to return (flag); here but how from thread?
		}
	}
	return (0);
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

static bool	philo(char **argv)
{
	t_vars	p;

	if (!parse_args(&p, argv) || p.n == 0 || (argv[5] && p.fed == 0))
		return (true);
	if (!threads_and_forks_init(&p) || !threads_run(&p) || !threads_join(&p))
		return (false);
	clean_up(&p);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || !valid_input(argv))
	{
		if (argc < 5)
			printf("%s\n", MSG_ARGS);
		printf("%s", MSG_PROMPT);
		return (EXIT_SUCCESS);
	}
	if (!philo(argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
