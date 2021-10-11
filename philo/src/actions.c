/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:34:54 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/07 08:54:41 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_status(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->restrictions->mutex.write);
	printf("[%lu]\t\t", (get_time_millisec()
			- philosopher->restrictions->simulation_start_time));
	printf("[%d]\t", philosopher->id);
//	printf("[%d]\t", philosopher->eating_counter);
	printf("%s\n", message);
	pthread_mutex_unlock(&philosopher->restrictions->mutex.write);
}

void	take_forks(t_philosopher *philosopher, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	print_status(philosopher, "\033[38;5;172mhas taken left fork\033[0m");
	pthread_mutex_lock(right_fork);
	print_status(philosopher, "\033[38;5;172mhas taken right fork\033[0m");
	philosopher->status = WITH_FORKS;
}

void	go_to_eat(t_philosopher *philo, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	print_status(philo, "\033[0;32mis eating\033[0m");
	philo->eating_start_time = get_time_millisec();
	action_time(philo->restrictions->time_to_eat);
	if (philo->restrictions->times_must_eat != -1)
		philo->eating_counter++;
	if (philo->restrictions->times_must_eat == philo->eating_counter)
		philo->restrictions->eat_control_counter++;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	philo->status = EATING;
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
