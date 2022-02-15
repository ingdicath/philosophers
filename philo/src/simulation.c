/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:11:16 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:11:16 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * Simulation per philosopher thread.
 * A LEFT and RIGHT fork is assigned to a philosopher.
 * Then an infinite loop runs the simulation until his dead.
 */
void	*run_simulation(void *arg)
{
	t_seat			*seat;
	t_philosopher	*philosopher;
	t_reservation	reservation;

	seat = arg;
	philosopher = seat->philosopher;
	if (philosopher->id % 2 != 0)
	{
		print_status(philosopher, CYAN, "is thinking", RESET);
		action_time(philosopher->restrictions->time_to_eat / 2);
	}
	assign_forks (&reservation, seat);
	while (philosopher->status != DIED
		&& philosopher->restrictions->allow_write == true)
	{
		if (philosopher->status == THINKING)
			take_forks(philosopher, reservation);
		else if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher, reservation);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
	return (NULL);
}

/**
 * Infinite loop over main thread.
 * It is used to monitoring each philosopher thread.
 */
void	check_philosopher_status(t_table *table)
{
	t_seat			*current_seat;
	t_philosopher	*curr_philosopher;

	current_seat = table->seats;
	while (current_seat)
	{
		curr_philosopher = current_seat->philosopher;
		if (curr_philosopher->eating_start_time
			+ curr_philosopher->restrictions->time_to_die < get_time_millisec())
		{
			change_philosopher_status(curr_philosopher, DIED);
			curr_philosopher->restrictions->allow_write = false;
			usleep(500);
			print_status(curr_philosopher, RED, "has died RIP", RESET);
			clean_seats(current_seat);
			break ;
		}
		if (check_enough_meals(current_seat) == true)
			break ;
		current_seat = current_seat->next;
	}
}

/**
 * When 'times_must_eat' parameter is set,
 * the program checks when the criteria is reached.
 */
bool	check_enough_meals(t_seat *seat)
{
	t_seat			*head;
	t_philosopher	*philo;

	philo = seat->philosopher;
	if (philo->restrictions->times_must_eat == -1)
		return (false);
	head = seat;
	while (seat->next != head)
	{
		if (philo->eating_counter < philo->restrictions->times_must_eat)
			return (false);
		seat = seat->next;
		philo = seat->philosopher;
	}
	if (philo->eating_counter < philo->restrictions->times_must_eat)
		return (false);
	usleep(500);
	philo->restrictions->allow_write = false;
	clean_seats(seat);
	printf("All philosophers have eaten enough.\n");
	return (true);
}
