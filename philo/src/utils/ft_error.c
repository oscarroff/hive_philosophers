/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:20:41 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:37:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd_endl(int fd, char *str)
{
	if (*str)
		if (write(fd, str, ft_strlen(str)) == ERROR
			|| write(fd, "\n", 1) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

int	ft_error(char *s, t_data *data)
{
	if (*s)
		if (ft_putstr_fd_endl(2, s) == ERROR)
			return (ERROR);
	if (data)
		philo_main_exit(data);
	return (ERROR);
}
