/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:19:27 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 11:57:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

long long	ft_super_atoi(const char *nptr)
{
	long long	res;
	int			sign;
	int			digit;

	res = 0;
	sign = 1;
	while (ft_isspace((int)*nptr))
		nptr++;
	if (ft_issign((int)*nptr))
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit((int)*nptr))
	{
		digit = (long)(*nptr - '0');
		res = res * 10 + (long)digit;
		if (res > INT_MAX + (long)1)
			return (res);
		nptr++;
	}
	return (res * sign);
}

bool	ft_atoui(unsigned int *nbr, const char *nptr)
{
	long long	res;

	if (!nptr)
		return (false);
	if (!ft_naun(nptr))
		return (false);
	res = ft_super_atoi(nptr);
	if (res > INT_MAX || res < 0)
		return (false);
	else
	{
		*nbr = (unsigned int)res;
		return (true);
	}
}
