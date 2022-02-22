/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philosophers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 15:03:13 by diani         #+#    #+#                 */
/*   Updated: 2022/02/14 15:03:13 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philosopher	*create_philosopher(int id, t_restrictions *restrictions)
{
	t_philosopher	*new_philosopher;

	new_philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!new_philosopher)
	{
		print_error("Error: can't create new philosopher");
		return (NULL);
	}
	new_philosopher->id = id;
	new_philosopher->status = THINKING;
	new_philosopher->eating_start_time = restrictions->simulation_start_time;
	new_philosopher->eating_counter = 0;
	new_philosopher->restrictions = restrictions;
	return (new_philosopher);
}

/**
 * A seat has a philosopher and a fork.
 */
t_seat	*create_seat(t_philosopher *philosopher)
{
	t_seat	*new_seat;

	new_seat = (t_seat *)malloc(sizeof(t_seat));
	if (!new_seat)
	{
		print_error("Error: can't create new seat");
		return (NULL);
	}
	new_seat->philosopher = philosopher;
	new_seat->fork_state = FREE;
	if (pthread_mutex_init(&new_seat->fork, NULL))
	{
		print_error("Error init pthread_mutex");
		return (NULL);
	}
	new_seat->next = NULL;
	return (new_seat);
}

/**
 * Adding a new seat with philosopher to a circular linked list.
 */
t_seat	*add_philosopher(t_seat **head, t_philosopher *philosopher)
{
	t_seat	*new_seat;

	new_seat = create_seat(philosopher);
	if (!new_seat)
		return (NULL);
	if (*head == NULL)
	{
		*head = new_seat;
		new_seat->next = *head;
	}
	else
	{
		new_seat->next = (*head)->next;
		(*head)->next = new_seat;
		*head = new_seat;
	}
	return (new_seat);
}

/**
 * Creating the table. Each philosopher has a seat.
 */
int	build_philosopher_table(t_restrictions *input, t_table *table,
							int seats_amount)
{
	int				i;
	t_philosopher	*philosopher;
	t_seat			*current_seat;

	i = 1;
	printf("%stime(ms)\tphilo\taction%s\n", CYAN, RESET);
	input->simulation_start_time = get_time_millisec();
	while (i <= seats_amount)
	{
		philosopher = create_philosopher(i, input);
		if (!philosopher)
			return (FAILURE);
		current_seat = add_philosopher(&table->seats, philosopher);
		if (!current_seat)
			return (FAILURE);
		if (pthread_create(&philosopher->thread, NULL, run_simulation,
				current_seat) != 0)
		{
			clean_seats(table->seats);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESSFUL);
}
