/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:56:52 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/06 14:57:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	get_time_millisec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	action_time(int action_time)
{
	unsigned long	start_sleep;

	start_sleep = get_time_millisec();
//	action_time *= 1000;
	while ((get_time_millisec() - start_sleep) < (unsigned)action_time)
		usleep(1000);
}
