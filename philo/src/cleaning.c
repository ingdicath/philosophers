/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:12:50 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:12:50 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_seats(t_seat *seat)
{
	t_seat	*temp;
	t_seat	*head;

	head = seat;
	while (seat->next != head)
	{
		temp = seat;
		seat = seat->next;
		free_all(temp);
	}
	free_all(seat);
}

void	free_all(t_seat *seat)
{
	pthread_mutex_destroy(&seat->fork);
	pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.death);
	pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.write);
	free(seat->philosopher);
	free(seat);
}
