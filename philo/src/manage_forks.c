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

void	take_forks(t_philosopher *philosopher, t_fork_reserved reserved)
{
	while (philosopher->restrictions->allow_write)
	{
		if (*reserved.left_state == FREE)
		{
			change_fork_state(reserved.left_fork, reserved.left_state, LEFT);
			print_status(philosopher, ORANGE, "has taken left fork", RESET);
		}
		if (*reserved.right_state == FREE)
		{
			change_fork_state(reserved.right_fork, reserved.right_state, RIGHT);
			print_status(philosopher, ORANGE, "has taken right fork", RESET);
		}
		if (*reserved.left_state == LEFT && *reserved.right_state == RIGHT)
		{
			change_philosopher_status(philosopher, WITH_FORKS);
			break ;
		}
	}
	usleep(100);
}

void	change_fork_state(pthread_mutex_t *fork, t_fork_state *fork_state,
						t_fork_state state)
{
	pthread_mutex_lock(fork);
	*fork_state = state;
	pthread_mutex_unlock(fork);
}

void	assign_right_fork(t_fork_reserved *reserved, pthread_mutex_t *fork,
						t_fork_state *state)
{
	reserved->right_fork = fork;
	reserved->right_state = state;
}

void	assign_left_fork(t_fork_reserved *reserved, pthread_mutex_t *fork,
						t_fork_state *state)
{
	reserved->left_fork = fork;
	reserved->left_state = state;
}
