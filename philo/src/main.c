/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/13 12:20:23 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "philo.h"

static bool	valid_input(char **argv);
static bool	philo(char **argv);

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

void	clean_up(t_vars *v)
{
	if (v->t)
		free(v->t);
	if (v->f)
		free(v->f);
}
