/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/21 18:28:46 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdatomic.h>
# include <limits.h>
# include <string.h>

// Successful execution
# define SUCCESS 1
// Unsuccessful execution
# define FAIL 0
// Error encountered
# define ERROR -1
// Conversion to hold seconds and miliseconds in one variable
# define USEC_PER_SEC 1000000LL
// Char check for updating last meal time
# define EATING 'a'
// Char check for updating last meal time
# define SLEEPING 'l'
// Odd result of % 2 for odd numbered philosophers
# define ODD 1
// Even result of % 2 for even numbered philosophers
# define EVEN 0
// Thread successful execution
# define THREAD_SUCCESS NULL
// Thread unsuccessful execution
# define THREAD_ERROR ((void *)-1)
// All philosopher threads closed
# define DONE 0

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
	atomic_bool		*fork_l;
	atomic_bool		*fork_r;
	pthread_mutex_t	*lock_l;
	pthread_mutex_t	*lock_r;
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
typedef struct s_data
{
	uint32_t					n;
	uint32_t					die;
	uint32_t					eat;
	uint32_t					sleep;
	uint32_t					fed;
	uint32_t					start;
	atomic_uint					i;
	atomic_bool					*f;
	pthread_mutex_t				*flock;
	atomic_uint_fast32_t		*ate;
	atomic_bool					*eating;
	atomic_bool					*dead;
	atomic_bool					*done;
	atomic_bool					end;
	pthread_t					*t;
	pthread_mutex_t				m;
}	t_data;

// philo
void	philo_main_exit(t_data *v);

// Initialisation
bool	parse_args(t_data *p, char **argv);

// Threads
int		threads_and_forks_init(t_data *v);
int		threads_run(t_data *v);
int		threads_join(t_data *v);

// Monitor
void	*monitor(void *data);

// Philosophise
void	*philo_odd(void *data);
void	*philo_even(void *data);
void	*philo_lonely(void *data);

// Do Things
int		go_eat_odd(t_philo *p, t_data *v);
int		go_eat_even(t_philo *p, t_data *v);

// Time
int		time_init(uint32_t *time);
int		time_fetch(uint32_t *time, uint32_t start);
int		atomic_time_fetch(atomic_uint_fast32_t *time, uint32_t start);
int		ft_usleep(uint32_t time, atomic_bool *end);

// Utilities
int		ft_isdigit(int c);
int		ft_issign(int c);
int		ft_isspace(int c);
bool	ft_naun(const char *nptr);
bool	ft_atoui(unsigned int *nbr, const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_error(char *s, t_data *data);

#endif
