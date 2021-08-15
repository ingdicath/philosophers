//
// Created by Diani on 07/08/2021.
//

#include "../includes/philosophers.h"

unsigned long	get_time_millisec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

// function to find how many time a philo spends doing an action
void	fix_sleep_accuracy(unsigned long time_to_sleep)
{
	unsigned long	start_time_sleep;

	start_time_sleep = get_time_millisec();
	while ((get_time_millisec() - start_time_sleep) < time_to_sleep)
		usleep(100);
}

void action_time(int action_time)
{
	unsigned long start_sleep;

	start_sleep = get_time_millisec();
	while((get_time_millisec() - start_sleep) < (unsigned)action_time)
		usleep(10);
}


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