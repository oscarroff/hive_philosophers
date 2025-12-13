/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:10:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/13 13:01:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "messages.h"

static void	vars_init(t_vars *p);

bool	parse_args(t_vars *p, char **argv)
{
	vars_init(p);
	if (!ft_atoui(&p->n, argv[1])
		|| !ft_atoui(&p->die, argv[2])
		|| !ft_atoui(&p->eat, argv[3])
		|| !ft_atoui(&p->sleep, argv[4]))
	{
		printf("%s\n", MSG_VALID);
		printf("%s", MSG_PROMPT);
		return (false);
	}
	if (argv[5])
	{
		if (!ft_atoui(&p->fed, argv[5]))
		{
			printf("%s\n", MSG_VALID);
			printf("%s", MSG_PROMPT);
			return (false);
		}
	}
	return (true);
}

static void	vars_init(t_vars *p)
{
	p->n = 0;
	p->die = 0;
	p->eat = 0;
	p->sleep = 0;
	p->fed = 0;
	p->i = 1;
	p->f = NULL;
	p->end = false;
	p->t = NULL;
	pthread_mutex_init(&p->m, NULL);
}
