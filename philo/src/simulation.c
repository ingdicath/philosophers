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
//	usleep((philosopher->id % 2) * 100000);
	if (philosopher->id % 2 != 0)
	{
		print_status(philosopher, CYAN,"is thinking", RESET);// new
		action_time(philosopher->restrictions->time_to_eat /2); //new
	}
	while (philosopher->status != DIED)
	{
		if (philosopher->status == THINKING)
			take_forks(philosopher, &seat->fork, &seat->next->fork);
		if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher, &seat->fork, &seat->next->fork);
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
		unsigned long deadT=  curr_philosopher->eating_start_time + curr_philosopher->restrictions->time_to_die;

		if (deadT < get_time_millisec())
		{
			pthread_mutex_lock(&curr_philosopher->restrictions->mutex.death);
			curr_philosopher->status = DIED;
			printf("hora muerte %lu %lu", deadT, get_time_millisec());
			print_status(curr_philosopher, RED, "has died ajajajajajajajajajajajajajajajajajajajajajajajaja", RESET);
			usleep(100);
			pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.death);
			break ;
		}
//		usleep(400); //new
		current_seat = current_seat->next;
	}
	control_eating(num_philosophers, curr_philosopher);
}

void	control_eating(int num_philosophers, const t_philosopher *curr_philosopher)
{
	if (curr_philosopher->restrictions->eat_control_counter >= num_philosophers)
	{
		usleep(100);
		pthread_mutex_lock(&curr_philosopher->restrictions->mutex.write);
		printf("All philosophers have eaten enough.\n");
		pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.write);
	}
}
