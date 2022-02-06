/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/11 14:01:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:47 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//static void	disable_threads(t_table *table, int num_philosophers)
//{
//	int		i;
//
//	i = 0;
//	while (i < num_philosophers)
//	{
//		pthread_detach(table->seats->philosopher->thread);
//		i++;
//	}
//}

/*
 * seat => One philosopher + one fork.
 */
void	*run_simulation(void *arg)
{
	t_seat			*seat;
	t_philosopher	*philosopher;

	seat = arg;
	philosopher = seat->philosopher;
	if (philosopher->id % 2 != 0)
	{
		print_status(philosopher, CYAN, "is thinking", RESET);// new
//		usleep(20000);
		action_time(philosopher->restrictions->time_to_eat / 2); //new
	}
//	pthread_mutex_t* left_fork = &seat->fork;
//	pthread_mutex_t* right_fork = &seat->next->fork;

	while (philosopher->status != DIED)
	{
		if (philosopher->status == THINKING)
			take_forks(seat);
		else if (philosopher->status == WITH_FORKS)
			go_to_eat(seat);
		else if (philosopher->status == EATING)
			go_to_sleep(philosopher);
		else if (philosopher->status == SLEEPING)
			go_to_think(philosopher);

	}
	return (NULL);
}

//int	monitor_meals(t_table *table *philo, int philosophers, pthread_t *threads)
//{
//	int	i;
//
//	i = 0;
//	while (i < philosophers)
//	{
//		if (philo[i].meals_eaten < philo->data->meals)
//			return (0);
//		i++;
//	}
//	philo->data->shutdown = true;
//	usleep(500);
//	shutdown_threads(threads, philosophers);
//	final_cleanup(philo, threads);
//	return (1);
//}

void	check_philosopher_status(t_table *table, int num_philosophers)
{
	t_seat			*current_seat;
	t_philosopher	*curr_philosopher;
	unsigned long	dead_time;
	unsigned long	time;

	current_seat = table->seats;
	curr_philosopher = current_seat->philosopher;
	while (current_seat && curr_philosopher->restrictions->eat_control_counter
		< num_philosophers)
	{

		curr_philosopher = current_seat->philosopher;

		time = get_time_millisec();

		dead_time = curr_philosopher->eating_start_time + curr_philosopher->restrictions->time_to_die;
//		if ((get_time_millisec() - curr_philosopher->eating_start_time) >= (unsigned long)curr_philosopher->restrictions->time_to_die)
		if (dead_time < time)
		{
			pthread_mutex_lock(&curr_philosopher->restrictions->mutex.death);
			printf("\n\nhora muerte %lu %lu %lu\n\n", dead_time, time, time-dead_time); //quitar
			curr_philosopher->status = DIED;
			print_status(curr_philosopher, RED, "has died ajajajajajajajajajajajajajajajajajajajajajajajaja", RESET);
			//usleep(100);
			pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.death);
			//disable_threads(table, num_philosophers); //new 26jan
			break ;
		}

		current_seat = current_seat->next;
//		usleep(10000); //estaba funcionando con 10000


	}
	eating_control(num_philosophers, curr_philosopher);
}

void	eating_control(int num_philos, const t_philosopher *curr_philosopher)
{
	if (curr_philosopher->restrictions->eat_control_counter >= num_philos)
	{
//		usleep(100);
		pthread_mutex_lock(&curr_philosopher->restrictions->mutex.write);
		printf("All philosophers have eaten enough.\n");
		pthread_mutex_unlock(&curr_philosopher->restrictions->mutex.write);
	}
}
