/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:34:54 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:23 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_status(t_philosopher *philosopher, char *start_color,
		char *message, char *reset_color)
{
	pthread_mutex_lock(&philosopher->restrictions->mutex.write);
	printf("[%lu]\t\t", (get_time_millisec()
			- philosopher->restrictions->simulation_start_time));
	printf("[%d]\t", philosopher->id);
	printf("[%d]\t", philosopher->eating_counter); //quitar
	printf("%s%s%s\n", start_color, message, reset_color);
	pthread_mutex_unlock(&philosopher->restrictions->mutex.write);
}

void	take_forks(t_philosopher *philosopher, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	print_status(philosopher, ORANGE, "has taken left fork", RESET);
	pthread_mutex_lock(right_fork);
	print_status(philosopher, ORANGE, "has taken right fork", RESET);
	philosopher->status = WITH_FORKS;
	usleep(100); //new
}

void	go_to_eat(t_philosopher *philo, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	philo->eating_start_time = get_time_millisec();
	print_status(philo, GREEN, "is eating", RESET);
	action_time(philo->restrictions->time_to_eat);
	if (philo->restrictions->times_must_eat != -1)
		philo->eating_counter++;
	if (philo->restrictions->times_must_eat == philo->eating_counter)
		philo->restrictions->eat_control_counter++;
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	philo->status = EATING;
}

void	go_to_sleep(t_philosopher *philosopher)
{
	print_status(philosopher, PURPLE, "is sleeping", RESET);
	action_time(philosopher->restrictions->time_to_sleep);
	philosopher->status = SLEEPING;
}

void	go_to_think(t_philosopher *philosopher)
{
	print_status(philosopher, CYAN, "is thinking", RESET);
	philosopher->status = THINKING;
}
