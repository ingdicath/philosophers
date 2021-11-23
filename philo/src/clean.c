/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:41:46 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/06 14:41:52 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//void	clean_table(t_seat **table)
//{
//	t_seat	*temp;
//
//	while (*table != NULL)
//	{
//		temp = *table;
//		*table = (*table)->next;
//		free(temp);
//	}
//}

void	clean_seats(t_seat *seat)
{
	t_seat	*temp;

	while (seat != NULL)
	{
		temp = seat;
		seat = seat->next;
		free(temp);
	}
}

void	clean_mutexes(t_seat *seat, int number_of_philosophers)
{
	int	i;

	i = 0;
	if (seat)
	{
//		while (i < number_of_philosophers) //
//		{
//			pthread_join(seat->philosopher->thread, NULL);//
//			i++;//
//		}//
//		i = 0;//
		while (i < number_of_philosophers)
		{
			pthread_mutex_destroy(&seat->fork);
			i++;
		}
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.death);
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.write);
	}
}

/*
 * Tengo que limpiar:
 * 1. philosopher (tabla)
 * 2. seat
 * 3. destroy mutex del fork
 * 4. destroy mutex de death
 * 5. destroy mutex de write
 */
