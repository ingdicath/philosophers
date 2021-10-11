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
	usleep((philosopher->id % 2) * 100);
	while (philosopher->status != DIED)
	// con la siguiente linea tampoco se arregla el problema
//	while (philosopher->status != DIED || philosopher->eating_counter < philosopher->restrictions->times_must_eat ) //aqui toca agregar las veces que ha comido
	{
		if (philosopher->status == THINKING)
		{
			usleep(100);
			take_forks(philosopher, &seat->prev->fork, &seat->fork);
		}
		if (philosopher->status == WITH_FORKS)
		{
			usleep(100);
			go_to_eat(philosopher, &seat->prev->fork, &seat->fork);
		}
		else if (philosopher->status == EATING)
		{
			usleep(100);
			go_to_sleep(philosopher);
		}
		else if (philosopher->status == SLEEPING)
		{
			usleep(100);
			go_to_think(philosopher);
		}
	}
	return (NULL);
}

void	check_philosopher_status(t_table *table, int num_philosophers)
{
	t_seat			*current_seat;
	t_philosopher	*curr_philosopher;

	current_seat = table->seats;
	curr_philosopher = current_seat->philosopher;
	while (current_seat && curr_philosopher->restrictions->eat_control_counter < num_philosophers)
	{
		curr_philosopher = current_seat->philosopher;
		if ((get_time_millisec() - curr_philosopher->eating_start_time)
			>= (unsigned long)curr_philosopher->restrictions->time_to_die)
		{
			pthread_mutex_lock(&curr_philosopher->restrictions->mutex.death);
			curr_philosopher->status = DIED;
			print_status(curr_philosopher, "\033[0;31mhas died\033[0m");
			pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.death);
			break ;
		}
		current_seat = current_seat->next;
	}
	// aqui no deberia ir algo para evitar que siga escribiendo despues de la muerte?? o algo para terminar los threads?
	if (curr_philosopher->restrictions->eat_control_counter >= num_philosophers)
	{
		usleep(100);
		pthread_mutex_lock(&curr_philosopher->restrictions->mutex.write);
		printf("All philosophers have eaten enough.\n");
		pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.write);
	}
}
