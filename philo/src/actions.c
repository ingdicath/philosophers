//
// Created by Diani on 14/08/2021.
//

#include "../includes/philosophers.h"

int	print_on_screen(t_philosopher *philosopher, char *message)
{
	// deberia incluir algo como write_mutex
	return (1);
}

void	take_forks(t_philosopher *philosopher, pthread_mutex_t left_fork, pthread_mutex_t right_fork)
{
	pthread_mutex_lock(left_fork);
	print_on_screen(philosopher, "has taken a fork\n");
	pthread_mutex_lock(right_fork);
	print_on_screen(philosopher, "has taken a fork\n");
	philosopher->status = WITH_FORKS;
}

void	go_to_eat(t_philosopher *philosopher, pthread_mutex_t left_fork, pthread_mutex_t right_fork)
{
	print_on_screen(philosopher, "is eating\n");
	philosopher->eating_start_time = get_time_millisec();
	action_time(philosopher->input.time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	philosopher->status = EATING;
}

void	go_to_sleep(t_philosopher *philosopher)
{
	print_on_screen(philosopher, "is sleeping\n");
	action_time(philosopher->input.time_to_sleep);
	philosopher->status = SLEEPING;
}

void	is_thinking(t_philosopher *philosopher)
{
	print_on_screen(philosopher, "is thinking\n");
	philosopher->status = THINKING;
}

/*
 * seat => philosopher + fork
 */
void	*start_simulation(void *arg)
{
	t_node			*seat;
	t_philosopher	*philosopher;

	seat = arg;
	philosopher = seat->philosopher;
	while (philosopher->status != DIED)
	{
		if (philosopher->status == THINKING)
			take_forks(philosopher, seat->prev->fork, seat->fork);
		if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher, seat->prev->fork, seat->fork);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
	return (NULL);
}
