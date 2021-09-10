//
// Created by Diani on 14/08/2021.
//

#include "../includes/philosophers.h"

void	print_status(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->restrictions->mutex.write);
	printf("[%lu]\t\t", (get_time_millisec() - philosopher->restrictions->simulation_start_time));
	printf("[%d]\t",philosopher->id);
	printf("%s\n", message);
	pthread_mutex_unlock(&philosopher->restrictions->mutex.write);
}

void	take_forks(t_philosopher *philosopher, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	print_status(philosopher, "\033[38;5;172mhas taken left fork\033[0m");
	pthread_mutex_lock(right_fork);
	print_status(philosopher, "\033[38;5;172mhas taken right fork\033[0m");
	philosopher->status = WITH_FORKS;
}

void	go_to_eat(t_philosopher *philosopher, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	print_status(philosopher, "\033[0;32mis eating\033[0m");
	philosopher->eating_start_time = get_time_millisec();
	action_time(philosopher->restrictions->time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	philosopher->status = EATING;
}

void	go_to_sleep(t_philosopher *philosopher)
{
	print_status(philosopher, "\033[0;35mis sleeping\033[0m");
	action_time(philosopher->restrictions->time_to_sleep);
	philosopher->status = SLEEPING;
}

void	go_to_think(t_philosopher *philosopher)
{
	print_status(philosopher, "\033[0;36mis thinking\033[0m");
	philosopher->status = THINKING;
}

/*
 * seat => One philosopher + one fork.
 */
void	*run_simulation(void *arg)
{
	t_seat			*seat;
	t_philosopher	*philosopher;
//	int	count_times_to_eat;

	seat = arg;
	philosopher = seat->philosopher;
//	count_times_to_eat = -1;
	usleep((philosopher->id % 2) * 100);
	while (philosopher->status != DIED)
//		&& count_times_to_eat < philosopher->restrictions->times_must_eat)
	{
//		dprintf(2, "start simulation 2\n"); //borrar
//		printf("status philo: %d\n", philosopher->status);
//		printf("status REAL: %d\n", THINKING);
//		printf("id philo: %d\n", philosopher->id);
		if (philosopher->status == THINKING)
		{
			take_forks(philosopher, &seat->prev->fork, &seat->fork);
		}
		if (philosopher->status == WITH_FORKS)
		{
			go_to_eat(philosopher, &seat->prev->fork, &seat->fork);
//			fix_sleep_accuracy(philosopher->restrictions->time_to_eat); //revisar si es necesario
		}
		else if (philosopher->status == EATING)
		{
			go_to_sleep(philosopher);
//			fix_sleep_accuracy(philosopher->restrictions->time_to_sleep); //revisar si es necesario
		}
		else if (philosopher->status == SLEEPING)
		{
			go_to_think(philosopher);
		}
	}
	return (NULL);
}

void check_philosopher_status(t_table *table)
{
	t_seat			*current_seat;
	t_philosopher	*current_philosopher;

	current_seat = table->seats;
	while(current_seat)
	{
//		usleep(100);
		current_philosopher = current_seat->philosopher;
//		pthread_mutex_lock(&current_philosopher->restrictions->mutex.death);
		if((get_time_millisec() - current_philosopher->eating_start_time) >=
			(unsigned long)current_philosopher->restrictions->time_to_die)
		{
			pthread_mutex_lock(&current_philosopher->restrictions->mutex.death);
			current_philosopher->status = DIED;
			print_status(current_philosopher,"\033[0;31mhas died\033[0m");
			pthread_mutex_unlock(&current_philosopher->restrictions->mutex.death);
			break;
		}
		current_seat = current_seat->next;
	}
}
