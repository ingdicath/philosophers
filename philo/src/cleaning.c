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
	t_seat  *head;
	head = seat;

	while (seat->next != head)
	{
		temp = seat;
		seat = seat->next;
		free_all(temp);
	}
	free_all(seat);
}


void free_all(t_seat *seat) {
	pthread_mutex_destroy(&seat->fork);
	pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.death);
	pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.write);
	free(seat->philosopher);
	free(seat);
}


/*
 * struct node* temp;

      if (head == NULL)
        return;

    // Find the required node
    struct Node *curr = head, *prev;
    while (curr->data != key)
    {
        if (curr->next == head)
        {
            printf("\nGiven node is not found"
                   " in the list!!!");
            break;
        }

        prev = curr;
        curr = curr->next;
    }

    // Check if node is only node
    if (curr->next == head)
    {
        head = NULL;
        free(curr);
        return;
    }

    // If more than one node, check if
    // it is first node
    if (curr == head)
    {
        prev = head;
        while (prev->next != head)
            prev = prev->next;
        head = curr->next;
        prev->next = head;
        free(curr);
    }

    // check if node is last node
    else if (curr->next == head && curr == head)
    {
        prev->next = head;
        free(curr);
    }
    else
    {
        prev->next = curr->next;
        free(curr);
    }
 * */

void	clean_mutexes(t_seat *seat, int number_of_philosophers)
{
	int	i;

	i = 0;
	if (seat)
	{
		while (i < number_of_philosophers)
		{
			pthread_mutex_destroy(&seat->fork);
			i++;
		}
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.death);
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.write);
	}
}
