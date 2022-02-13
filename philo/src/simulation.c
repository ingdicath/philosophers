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


void go_to_eat(t_philosopher *philo) {
	change_philosopher_status(philo, EATING);

	philo->eating_start_time = get_time_millisec();
	print_status(philo, GREEN, "is eating", RESET);
	action_time(philo->restrictions->time_to_eat);
	if (philo->restrictions->times_must_eat != -1)
		philo->eating_counter++;
	change_fork_status(philo->xxx.left_fork, philo->xxx.left_state, FREE);
	change_fork_status(philo->xxx.right_fork, philo->xxx.right_state, FREE);

}

void change_fork_status(pthread_mutex_t *fork, t_fork_state *fork_state, t_fork_state state) {
	pthread_mutex_lock(fork);
	*fork_state = state;
	pthread_mutex_unlock(fork);
}

void change_philosopher_status(t_philosopher *philo, t_status status)
{
	pthread_mutex_lock(&philo->restrictions->mutex.death);
	if (philo->status != DIED)
		philo->status = status;
	pthread_mutex_unlock(&philo->restrictions->mutex.death);
}

void take_forks(t_philosopher *philosopher) {

	while (philosopher->restrictions->allow_write) {
		if (*philosopher->xxx.left_state == FREE) {
			change_fork_status(philosopher->xxx.left_fork, philosopher->xxx.left_state, LEFT);
			print_status(philosopher, ORANGE, "has taken left fork", RESET);
		}
		if (*philosopher->xxx.right_state == FREE) {
			change_fork_status(philosopher->xxx.right_fork, philosopher->xxx.right_state, RIGHT);
			print_status(philosopher, ORANGE, "has taken right fork", RESET);
		}
		if (*philosopher->xxx.left_state == LEFT && *philosopher->xxx.right_state == RIGHT) {
			change_philosopher_status(philosopher, WITH_FORKS);
			break;
		}
	}
	usleep(100);
}

/**
 * seat => One philosopher + one fork.
 */
void *run_simulation(void *arg)
{
	t_seat *seat;
	t_philosopher *philosopher;

	seat = arg;
	philosopher = seat->philosopher;
	if (philosopher->id % 2 != 0) {
		print_status(philosopher, CYAN, "is thinking", RESET);
		action_time(philosopher->restrictions->time_to_eat /2);
	}
	assign_left_fork(philosopher,&seat->fork, &seat->fork_state);
	assign_right_fork(philosopher,&seat->next->fork, &seat->next->fork_state);
	while (philosopher->status != DIED) {
		if (philosopher->status == THINKING)
			take_forks(philosopher);
		else if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
	return (NULL);
}

void assign_right_fork(t_philosopher *philosopher, pthread_mutex_t *fork, t_fork_state *state) {
	philosopher->xxx.right_fork = fork;
	philosopher->xxx.right_state = state;
}

void assign_left_fork(t_philosopher *philosopher, pthread_mutex_t *fork, t_fork_state *state) {
	philosopher->xxx.left_fork = fork;
	philosopher->xxx.left_state = state;
}

//ciclo infinito sobre main thread
void check_philosopher_status(t_table *table, int num_philosophers) {
	t_seat *current_seat;
	t_philosopher *curr_philosopher;
	unsigned long dead_time;
	unsigned long time;
	int control_counter;

	control_counter = 0;
	current_seat = table->seats;
	while (current_seat ) {
		curr_philosopher = current_seat->philosopher;
		time = get_time_millisec();
		dead_time = curr_philosopher->eating_start_time
					+ curr_philosopher->restrictions->time_to_die;
		if (dead_time < time) {
			change_philosopher_status(curr_philosopher, DIED);
			curr_philosopher->restrictions->allow_write = 0;
			usleep(500);
			print_status(curr_philosopher, RED, "has died RIP", RESET);
			clean_seats(current_seat);
			break;
		}
		if (curr_philosopher->eating_counter
			>= curr_philosopher->restrictions->times_must_eat
			&& curr_philosopher->restrictions->times_must_eat != -1)
			control_counter++;
		else
			control_counter = 0;
		if (control_counter == num_philosophers)
			break;
		current_seat = current_seat->next;
	}

	if (control_counter == num_philosophers) {
		usleep(500);
		pthread_mutex_lock(&curr_philosopher->restrictions->mutex.write);
		printf("All philosophers have eaten enough.\n");
		pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.write);
		clean_seats(current_seat);
	}
}



