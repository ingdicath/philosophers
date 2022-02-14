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

void	reserve_right(t_reservation *reservation, pthread_mutex_t *fork,
					t_fork_state *state)
{
	reservation->right_fork = fork;
	reservation->right_state = state;
}

void	reserve_left(t_reservation *reservation, pthread_mutex_t *fork,
					t_fork_state *state)
{
	reservation->left_fork = fork;
	reservation->left_state = state;
}

void	change_fork_state(pthread_mutex_t *fork, t_fork_state *fork_state,
						t_fork_state state)
{
	pthread_mutex_lock(fork);
	*fork_state = state;
	pthread_mutex_unlock(fork);
}

/**
 * A philosopher is trying to reserve forks to be able to eat.
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
