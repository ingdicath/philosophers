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


void makeItStop(t_seat *pSeat);



void go_to_eat(t_philosopher *philo, pthread_mutex_t *left_fork,
			   pthread_mutex_t *right_fork, t_fork_state *left_state,
			   t_fork_state *right_state) {
	change_philosopher_status(philo, EATING);

	philo->eating_start_time = get_time_millisec();
	print_status(philo, GREEN, "is eating", RESET);
	action_time(philo->restrictions->time_to_eat);
	if (philo->restrictions->times_must_eat != -1)
		philo->eating_counter++;
	pthread_mutex_lock(left_fork);
	*left_state = FREE;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_lock(right_fork);
	*right_state = FREE;
	pthread_mutex_unlock(right_fork);
}

void change_philosopher_status(t_philosopher *philo, t_status status)
{
	pthread_mutex_lock(&philo->restrictions->mutex.death);
	if (philo->status != DIED)
		philo->status = status;
	pthread_mutex_unlock(&philo->restrictions->mutex.death);
}

void take_forks(t_philosopher *philosopher, pthread_mutex_t *left_fork,
				pthread_mutex_t *right_fork, t_fork_state *left_state,
				t_fork_state *right_state) {

	while (philosopher->restrictions->allow_write) {
		pthread_mutex_lock(left_fork);
		if (*left_state == FREE) {
			*left_state = LEFT;
			print_status(philosopher, ORANGE, "has taken left fork", RESET);
		}
		pthread_mutex_unlock(left_fork);
		pthread_mutex_lock(right_fork);
		if (*right_state == FREE) {
			*right_state = RIGHT;
			print_status(philosopher, ORANGE, "has taken right fork", RESET);
		}
		pthread_mutex_unlock(right_fork);
		if (*left_state == LEFT && *right_state == RIGHT) {
			change_philosopher_status(philosopher, WITH_FORKS);
			break;
		}
	}
	usleep(100);
}

//void shutdown_threads(t_seat *current_seat) {
//	t_philosopher *curr_philosopher;
//	while (current_seat) {
//		curr_philosopher = current_seat->philosopher;
//		pthread_detach(curr_philosopher->thread);
//		current_seat = current_seat->next;
//	}
//}

/**
 * seat => One philosopher + one fork.
 */
void *run_simulation(void *arg) {
	t_seat *seat;
	t_philosopher *philosopher;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_fork_state *left_state;
	t_fork_state *right_state;

	seat = arg;
	philosopher = seat->philosopher;
	if (philosopher->id % 2 != 0) {
		print_status(philosopher, CYAN, "is thinking", RESET);
		action_time(philosopher->restrictions->time_to_eat /2);

	}
	left_fork = &seat->fork;
	right_fork = &seat->next->fork;
	left_state = &seat->fork_state;
	right_state = &seat->next->fork_state;
	philosopher = seat->philosopher;

	while (philosopher->status != DIED) {
		if (philosopher->status == THINKING)
			take_forks(philosopher, left_fork, right_fork, left_state, right_state);
		else if (philosopher->status == WITH_FORKS)
			go_to_eat(philosopher, left_fork, right_fork, left_state, right_state);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);
	}
	return (NULL);
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

void makeItStop(t_seat *seat) {
	t_seat  *head;
	head = seat;
//	printf("estado %d\n", seat->philosopher->status);
	seat = seat->next;
	while (seat != head)
	{
		seat->philosopher->status = STOP;
//		printf("estado %d\n", seat->philosopher->status);
		seat = seat->next;
	}

}


