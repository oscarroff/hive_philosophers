/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_eat_odd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:41:59 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/23 14:46:22 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_cutlery_odd(t_philo *p, t_data *v);

int	go_eat_odd(t_philo *p, t_data *v)
{
	if (take_cutlery_odd(p, v) == ERROR)
		return (ft_error("take_cutlery_odd() fail", NULL));
	if (what_you_doing("eating", p, v) == ERROR)
		return (ft_error("what_you_doing() fail", NULL));
	if (ft_usleep(v->eat, &v->end) == ERROR)
		return (ft_error("ft_usleep() fail", NULL));
	if (return_cutlery(p, v) == ERROR)
		return (ft_error("return_cutlery() fail", NULL));
	return (SUCCESS);
}

static int	take_cutlery_odd(t_philo *p, t_data *v)
{
	if (take_fork(p->fork_r, p->lock_r, p, v) == ERROR)
		return (ft_error("take_fork() fail", NULL));
	if (take_fork(p->fork_l, p->lock_l, p, v) == ERROR)
		return (ft_error("take_fork() fail", NULL));
	return (SUCCESS);
}
