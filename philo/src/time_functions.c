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
		usleep(100);
}

// chequear esta funcion
//void	better_sleep(long d)
//{
//	struct timeval tmp;
//	struct timeval start;
//
//	gettimeofday(&start, NULL);
//	while (1)
//	{
//		usleep(50);
//		gettimeofday(&tmp, NULL);
//		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000 + ((long)(tmp.tv_usec - start.tv_usec))) >= d)
//			return ;
//	}
//}

// for usleep() inaccuracy
//static void    stupid_sleep(unsigned long ms)
//{
//	unsigned long    entry;
//
//	entry = get_time_us();
//	ms *= 1000;
//	while ((get_time_us() - entry) < ms)
//		usleep(100);
//}