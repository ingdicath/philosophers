//
// Created by Diani on 13/07/2021.
//

#include "../includes/philosophers.h"

t_philosopher	*create_philosopher(int id, t_restrictions *restrictions, unsigned long eating_start_time) //revisar si es necesario incluir mutex para fork
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
	new_philo->restrictions = restrictions;
	new_philo->restrictions->times_must_eat = 0; // REVISAR ESTOOOOOOOOOOOOOOOOOOOOO
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
//	dprintf(2, "add_philosopher 1\n"); //borrar
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
int	build_philosopher_table(t_restrictions *input, t_table *table, int seats_amount) //faltaria incluir validacion en caso que add philosopher falle?
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
		if (pthread_create(&philosopher->thread, NULL, run_simulation, current_seat) != 0) //revisar si toca poner condicional
			return (-1); //revisar este valor de error
		i++;
	}


//	dprintf(2, "[%d] build_philo_table 5, sale del while\n", i);
//	i = 1;
//	while (i <= seats_amount)
//	{
//		if (pthread_join(philosopher->thread, NULL))
//			return (-1);
//		usleep(100);
//		if (pthread_join(philosopher->state, NULL))
//			return (-1);
//		i++;
//	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_restrictions	restrictions;
	t_table	table;
	int	number_of_philosophers;

	table.seats = NULL;
	if (argc < 5 || argc > 6)
		return (print_error("Number of arguments is not correct"));
	else if (parsing(argv, &restrictions, &number_of_philosophers) == -1)
		return (print_error("Invalid arguments"));
	printf("\033[0;36mtime(ms)\tphilo\taction\033[0m\n");
	build_philosopher_table(&restrictions, &table, number_of_philosophers);
	check_philosopher_status(&table);

//	t_seat			*current_seat;
//	current_seat = table.seats;
//	while(current_seat)
//	{
//		pthread_join(table.seats->philosopher->thread, NULL);
//		current_seat = current_seat->next;
//		if(current_seat == table.seats)
//			break;
//	}
	return (0);
}
