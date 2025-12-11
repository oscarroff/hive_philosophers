/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_naun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:39:22 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 11:53:13 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_naun(const char *nptr)
{
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
		return (false);
	if (!ft_isdigit(*nptr))
		return (false);
	while (ft_isdigit(*nptr))
		nptr++;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr)
		return (false);
	else
		return (true);
}
