//
// Created by Diani on 13/07/2021.
//

#include "../includes/philosophers.h"

t_philosopher	*create_philosopher(int id, struct timeval eating_start_time) //revisar si es necesario incluir mutex para fork
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
//	pthread_mutex_init(&new_philo->fork, NULL);
	return (new_philo);
}

t_node	*create_node(t_philosopher *philosopher)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
	{
		print_error("Error: can't create new node");
		return (NULL);
	}
	new_node->philosopher = philosopher;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/*
 * enqueueing each new element
 */
t_node	*add_philosopher(t_node **head, t_philosopher *philosopher)
{
	t_node	*new_element;
	t_node	*tail;

	new_element = create_node(philosopher);
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
 * creating the whole table
 */
int	build_philo_table(t_input input, t_node **table)
{
	int				i;
	t_philosopher	*philosopher;
	t_node			*philosopher_node;
	struct timeval	initial_time;

	i = 1;
	gettimeofday(&initial_time, NULL);
	while (i <= input.number_of_philosophers)
	{
		philosopher = create_philosopher(i, initial_time);
		philosopher_node = add_philosopher(table, philosopher);
		pthread_create(&philosopher->thread, NULL, start_simulation,
			&philosopher_node);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc < 5 || argc > 6)
		return (print_error("Number of arguments is not correct"));
	else if (parsing(argv, &input) == -1)
		return (print_error("Invalid arguments"));
	printf("time(ms)\tphilo\t\taction\n");
	return (0);
}
