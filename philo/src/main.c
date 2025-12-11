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

#include "philo.h"
#include "messages.h"

static bool	philo(char **argv)
{
	t_philo	p;

	if (!parse_args(&p, argv))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("%s\n", MSG_ARGS);
		printf("%s", MSG_PROMPT);
		return (EXIT_SUCCESS);
	}
	if (!valid_input(argv) || !philo(argv))
	{
		printf("%s\n", MSG_VALID);
		printf("%s", MSG_PROMPT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
