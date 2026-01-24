/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/24 11:54:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "philo.h"

static int	valid_input(char **argv);
static int	philo_main(char **argv);

int	main(int argc, char **argv)
{
	int		flag;

	if (argc < 5)
	{
		printf("%s\n", MSG_ARGS);
		return (EXIT_SUCCESS);
	}
	if (valid_input(argv) == FAIL)
		return (EXIT_SUCCESS);
	flag = philo_main(argv);
	if (flag == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	valid_input(char **argv)
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
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

static int	philo_main(char **argv)
{
	t_data	v;
	int		flag;

	flag = parse_args(&v, argv);
	if (flag != SUCCESS)
		return (flag);
	if (init(&v) == ERROR)
		return (philo_init_exit(&v));
	if (threads_run(&v) == ERROR)
		return (philo_threads_exit(&v));
	flag = threads_join(&v);
	if (philo_main_exit(&v) == ERROR)
		flag = ERROR;
	return (flag);
}
