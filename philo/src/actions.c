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

/**
 *lock to change status only
 */

void	take_forks(t_seat *seat)
{
	pthread_mutex_t *left_fork = &seat->fork;
	t_fork_state * left_state= &seat->fork_state;
	t_philosopher *philosopher = seat->philosopher;
	pthread_mutex_t *right_fork = &seat->next->fork;
	t_fork_state * right_state= &seat->next->fork_state;
	pthread_mutex_lock(left_fork);

	while (*right_state != BORROWED && *left_state != TAKEN )
	{
		if (*left_state == FREE)
		{
			*left_state = TAKEN;
			print_status(philosopher, ORANGE, "has taken left fork", RESET);
		}
		pthread_mutex_unlock(left_fork);
		pthread_mutex_lock(right_fork);
		if (*right_state == FREE)
		{
			*right_state = BORROWED;
			print_status(philosopher, ORANGE, "has taken right fork", RESET);
		}
		pthread_mutex_unlock(right_fork);
	}
	if (seat->next != seat)
		philosopher->status = WITH_FORKS;
}

void	go_to_eat(t_seat *seat)
{
	pthread_mutex_t *left_fork = &seat->fork;
	t_fork_state *left_state = &seat->fork_state;
	t_philosopher *philo = seat->philosopher;

	pthread_mutex_t *right_fork = &seat->next->fork;
	t_fork_state * right_state= &seat->next->fork_state;
	philo->status = EATING;

	print_status(philo, GREEN, "is eating", RESET);
	philo->eating_start_time = get_time_millisec();
	action_time(philo->restrictions->time_to_eat);

	pthread_mutex_lock(left_fork);
	*left_state = FREE;
	pthread_mutex_unlock(left_fork);

	pthread_mutex_lock(right_fork);
	*right_state = FREE;
	pthread_mutex_unlock(right_fork);
	if (philo->restrictions->times_must_eat != -1)
		philo->eating_counter++;
	if (philo->restrictions->times_must_eat == philo->eating_counter)
		philo->restrictions->eat_control_counter++;
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
