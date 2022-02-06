/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:56:52 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:53 by dsalaman      ########   odam.nl         */
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
//	action_time *= 1000; //new 28Jan
	start_sleep = get_time_millisec();
	while ((get_time_millisec() - start_sleep) < (unsigned)action_time)
		usleep(100);
}
