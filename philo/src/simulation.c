/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/11 14:01:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/09/11 16:42:56 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"



/*
 * seat => One philosopher + one fork.
 */
void	*run_simulation(void *arg)
{
	t_seat			*seat;
	t_philosopher	*philosopher;

	seat = arg;
	philosopher = seat->philosopher;
	usleep((philosopher->id % 2) * 100000);
	while (philosopher->status != DIED)
	{
		if (philosopher->status == THINKING)
			take_forks(philosopher, &seat->prev->fork, &seat->fork);
		if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher, &seat->prev->fork, &seat->fork);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
	return (NULL);
}

void	check_philosopher_status(t_table *table, int num_philosophers)
{
	t_seat			*current_seat;
	t_philosopher	*curr_philosopher;

	current_seat = table->seats;
	curr_philosopher = current_seat->philosopher;
	while (current_seat && curr_philosopher->restrictions->eat_control_counter
		< num_philosophers)
	{
		curr_philosopher = current_seat->philosopher;
		if ((get_time_millisec() - curr_philosopher->eating_start_time)
			>= (unsigned long)curr_philosopher->restrictions->time_to_die)
		{
			pthread_mutex_lock(&curr_philosopher->restrictions->mutex.death);
			curr_philosopher->status = DIED;
			print_status(curr_philosopher, RED, "has died ajajajajajajajajajajajajajajajajajajajajajajajaja", RESET);
			pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.death);
			break ;
		}
		current_seat = current_seat->next;
	}
	control_eating(num_philosophers, curr_philosopher);
}

void
control_eating(int num_philosophers, const t_philosopher *curr_philosopher) {
	if (curr_philosopher->restrictions->eat_control_counter >= num_philosophers)
	{
		usleep(100);
		pthread_mutex_lock(&curr_philosopher->restrictions->mutex.write);
		printf("All philosophers have eaten enough.\n");
		pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.write);
	}
}
