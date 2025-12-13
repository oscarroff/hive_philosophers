/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 13:11:43 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libc.h>
# include <pthread.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdatomic.h>

// Codes for error tracking
// Successful execution
# define SUCCESS 1
// Unsuccessful execution
# define FAIL 0
// Error encountered
# define ERROR -1

// Struct for each philosopher
// x: unique number of each philosopher
// meals: number of times a philosopher has eaten
// ate_s: timestamp of last meal in seconds
// ate_u: timestamp of last meal in miliseconds
// state: status of phlosopher
//		- a: alive
//		- e: eating
//		- s: sleeping
//		- t: thinking
//		- d: dead
// f1: fork to left of philosopher
// f2: fork to right of philosopher
typedef struct s_philo
{
	uint32_t		x;
	uint32_t		meals;
	atomic_ulong	ate_s;
	atomic_uint		ate_u;
	atomic_char		state;
	atomic_bool		*f1;
	atomic_bool		*f2;
}	t_philo;

// Struct for shared program variables
// n: number of philosophers
// die: time until a philosopher will die after their last meal
// eat: time a philosopher will spend eating
// sleep: time a philosopher will spend sleeping
// fed: number of times each philosopher must eat before simulation end
// i: counter for philosophers used to assign 'x' in t_philo
// f: forks a array of bools, either unused (false) or used (true)
// end: flag to end simulation if a philosopher dies
// t: system IDs of all threads
// m: mutex lock
typedef struct s_vars
{
	uint32_t		n;
	uint32_t		die;
	uint32_t		eat;
	uint32_t		sleep;
	uint32_t		fed;
	atomic_uint		i;
	atomic_bool		*f;
	atomic_bool		end;
	pthread_t		*t;
	pthread_mutex_t	m;
}	t_vars;

// philo

// Initialisation
bool	valid_input(char **argv);
bool	parse_args(t_vars *p, char **argv);

// Utilities
int		ft_isdigit(int c);
int		ft_issign(int c);
int		ft_isspace(int c);
bool	ft_naun(const char *nptr);
bool	ft_atoui(unsigned int *nbr, const char *nptr);

#endif
