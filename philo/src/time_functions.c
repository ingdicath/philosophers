/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:12:25 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:12:25 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	get_time_millisec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

/**
 * Sleep the thread in intervals of 100 microsec until reach
 * the milliseconds needed.
 */
void	action_time(int action_time)
{
	unsigned long	start_sleep;

	start_sleep = get_time_millisec();
	while ((get_time_millisec() - start_sleep) < (unsigned)action_time)
		usleep(100);
}
