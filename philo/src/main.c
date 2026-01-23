/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:04:43 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "philo.h"

static bool	valid_input(char **argv);
static bool	philo_main(char **argv);

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("%s\n", MSG_ARGS);
		return (EXIT_SUCCESS);
	}
	if (!valid_input(argv))
	{
		printf("%s", MSG_PROMPT);
		return (EXIT_SUCCESS);
	}
	if (!philo_main(argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	valid_input(char **argv)
{
	int	i;

	while (*++argv)
	{
		i = 0;
		while (argv[0][i])
		{
			if (!ft_isdigit(argv[0][i++]))
			{
				printf("%s\n", MSG_VALID);
				printf("%s", MSG_PROMPT);
				return (false);
			}
		}
	}
	return (true);
}

static bool	philo_main(char **argv)
{
	t_data	p;

	if (!parse_args(&p, argv) || p.n == 0 || (argv[5] && p.fed == 0))
		return (true);
	if (threads_and_forks_init(&p) == ERROR
		|| threads_run(&p) == ERROR
		|| threads_join(&p) == ERROR)
		return (false);
	philo_main_exit(&p);
	return (true);
}

void	philo_main_exit(t_data *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
		pthread_mutex_destroy(&v->flock[i++]);
	pthread_mutex_destroy(&v->m);
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
