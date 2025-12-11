/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:03 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 10:58:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define MSG_PROMPT \
"Philosophers usage:\n\
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \n\
[number_of_times_each_philosopher_must_eat]\n\n\
- number_of_philosophers: number of philosophers and forks\n\
- time_to_die (in milliseconds): if they have not eaten in this time, they die\n\
- time_to_eat (in milliseconds): time it takes for them to eat\n\
- time_to_sleep (in milliseconds): time they will spend sleeping\n\
- number_of_times_each_philosopher_must_eat (optional argument): if all have\n\
  eaten this number of times then simulation stops, otherwise it runs until\n\
  someone dies\n"
# define MSG_ARGS \
"Error: not enough arguments provided, philo expects a minimum of 4 \
arguments.\n"
# define MSG_VALID \
"Error: invalid input, philo expects arguments as unsigned integers only.\n"

#endif
