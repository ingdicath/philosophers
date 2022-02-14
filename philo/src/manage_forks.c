/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_forks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 23:49:23 by diani         #+#    #+#                 */
/*   Updated: 2022/02/13 23:49:23 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	assign_forks(t_reservation *reservation, t_seat *current_seat)
{
	reservation->left_fork = &current_seat->fork;
	reservation->left_state = &current_seat->fork_state;
	reservation->right_fork = &current_seat->next->fork;
	reservation->right_state = &current_seat->next->fork_state;
}

void	change_fork_state(pthread_mutex_t *fork, t_fork_state *current_state,
						t_fork_state new_state)
{
	pthread_mutex_lock(fork);
	*current_state = new_state;
	pthread_mutex_unlock(fork);
}

/**
 * A philosopher has to reserve both, LEFT and RIGHT forks to be able to eat.
 */
void	take_forks(t_philosopher *philosopher, t_reservation reservation)
{
	while (philosopher->restrictions->allow_write)
	{
		if (*reservation.left_state == FREE)
		{
			change_fork_state(reservation.left_fork,
				reservation.left_state, LEFT);
			print_status(philosopher, ORANGE, "has taken left fork", RESET);
		}
		if (*reservation.right_state == FREE)
		{
			change_fork_state(reservation.right_fork,
				reservation.right_state, RIGHT);
			print_status(philosopher, ORANGE, "has taken right fork", RESET);
		}
		if (*reservation.left_state == LEFT
			&& *reservation.right_state == RIGHT)
		{
			change_philosopher_status(philosopher, WITH_FORKS);
			break ;
		}
		usleep(100);
	}
}
