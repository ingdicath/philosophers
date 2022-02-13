/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:11:39 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:11:39 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_status(t_philosopher *philosopher, char *start_color,
		char *message, char *reset_color)
{

		pthread_mutex_lock(&philosopher->restrictions->mutex.write);
	if ( philosopher->status == DIED || philosopher->restrictions->allow_write)
	{
		printf("[%lu]\t\t", (get_time_millisec()
				- philosopher->restrictions->simulation_start_time));
		printf("[%d]\t", philosopher->id);
		printf("%s%s%s\n", start_color, message, reset_color);

	}
	pthread_mutex_unlock(&philosopher->restrictions->mutex.write);
}

/**
 *lock to change status only
 */
void	go_to_sleep(t_philosopher *philosopher)
{
	print_status(philosopher, PURPLE, "is sleeping", RESET);
	action_time(philosopher->restrictions->time_to_sleep);
	change_philosopher_status(philosopher, SLEEPING);
}

void	go_to_think(t_philosopher *philosopher)
{
	print_status(philosopher, CYAN, "is thinking", RESET);
	change_philosopher_status(philosopher, THINKING);
}
