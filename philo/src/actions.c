//
// Created by Diani on 14/08/2021.
//

#include "../includes/philosophers.h"

int	print_on_screen(t_philosopher *philosopher, char *message)
{
	// deberia incluir algo como write_mutex
	return (1);
}

//int	lock_fork(t_philosopher *philosopher)
//{
//	pthread_mutex_lock(philosopher->fork);
//	print_on_screen(philosopher, "has taken a fork\n");
//	return (1);
//}

int lock_right_fork(t_node **node)
{
	pthread_mutex_lock((*node)->data->fork);
	print_on_screen((*node)->data->id, "has taken a fork\n");
}

int lock_left_fork(t_node **node)
{
	pthread_mutex_lock((*node)->prev->data->fork);
	print_on_screen((*node)->data->id, "has taken a fork\n");
}

int take_forks(pthread_mutex_t left_fork, pthread_mutex_t right_fork)
{
	if((input.number_of_philosophers % 2) != 0)
	{
		if (lock_left_fork(((*node)->data->id))
			return (0);
	}
	return (1);
}

int	is_thinking(t_philosopher *philosopher)
{
	return (print_on_screen(philosopher, "is thinking\n"));
}

/*
 * seat => philosopher + fork
 */
void *start_simulation(void *arg)
{
	t_node			*seat;
	t_philosopher	*philosopher;

	seat = arg;
	philosopher = seat->philosopher;
	while (philosopher->status != DIED)
	{
		if (philosopher->status == THINKING)
			take_forks(seat->prev->fork, seat->fork);
		if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
//	return (NULL);
}
