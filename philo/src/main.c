/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:55:38 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/06 16:31:42 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philosopher	*create_philosopher(int id, t_restrictions *restrictions,
					unsigned long eating_start_time)
{
	t_philosopher	*new_philo;

	new_philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!new_philo)
	{
		print_error("Error: can't create new philosopher");
		return (NULL);
	}
	new_philo->id = id;
	new_philo->status = THINKING;
	new_philo->eating_start_time = eating_start_time;
	new_philo->eating_counter = 0;
	new_philo->restrictions = restrictions;
	return (new_philo);
}

/*
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
	pthread_mutex_init(&new_seat->fork, NULL);
	new_seat->prev = NULL;
	new_seat->next = NULL;
	return (new_seat);
}

/*
 * Enqueueing each new element.
 */
t_seat	*add_philosopher(t_seat **head, t_philosopher *philosopher)
{
	t_seat	*new_element;
	t_seat	*tail;

	new_element = create_seat(philosopher);
	if (*head == NULL)
	{
		*head = new_element;
		tail = new_element;
		tail->next = *head;
		tail->prev = *head;
	}
	else
	{
		tail = (*head)->prev;
		tail->next = new_element;
		new_element->prev = tail;
		new_element->next = *head;
		(*head)->prev = new_element;
	}
	return (new_element);
}

/*
 * Creating the table. A table has a certain amount of seats.
 */
int	build_philosopher_table(t_restrictions *input, t_table *table,
		int seats_amount) //faltaria incluir validacion en caso que add philosopher falle?
{
	int				i;
	unsigned long	initial_time;
	t_philosopher	*philosopher;
	t_seat			*current_seat;

	i = 1;
	initial_time = get_time_millisec();
	input->simulation_start_time = initial_time;
	while (i <= seats_amount)
	{
		philosopher = create_philosopher(i, input, initial_time);
		current_seat = add_philosopher(&table->seats, philosopher);
		if (pthread_create(&philosopher->thread, NULL, run_simulation,
				current_seat) != 0)
			return (FAILED); //revisar este valor de error
		i++;
	}
	return (SUCCESSFUL);
}

int	main(int argc, char **argv)
{
	t_restrictions	restrictions;
	t_table			table;
	int				number_of_philosophers;

	table.seats = NULL;
	if (argc < 5 || argc > 6)
		return (print_error("Number of arguments is not correct"));
	else if (parsing(argv, &restrictions, &number_of_philosophers) == FAILED)
		return (print_error("Invalid arguments"));
	printf("\033[0;36mtime(ms)\tphilo\taction\033[0m\n");
	if (build_philosopher_table(&restrictions, &table, number_of_philosophers) != SUCCESSFUL)
		return (print_error("Error building philosophers"));
	check_philosopher_status(&table, number_of_philosophers);
	clean_mutexes(table.seats, number_of_philosophers);

//    clean_seats(table.seats);
//    system("leaks philo");
	return (0);
}

/*
 * Tengo que limpiar:
 * 1. philosopher
 * 2. seat
 * 3. destroy mutex del fork
 * 4. destroy mutex de death
 * 5. destroy mutex de write
 */