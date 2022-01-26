/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:41:46 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:29 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_table(t_seat *seat, int number_of_philosophers)
{
	int		i;
	t_seat	*temp;

	i = 0;
	if (seat)
	{
		while (i < number_of_philosophers)
		{
			temp = seat;
			seat = seat->next;
			free(temp);
			i++;
		}
	}
}

//chequear como limpiar al philosopher
//void	clean_philosophers(t_philosopher *philo, int number_of_philosophers)
//{
//	int				i;
//	t_philosopher	*temp;
//
//	i = 0;
//	if (philo)
//	{
//		while (i < number_of_philosophers)
//		{
//			temp = philo;
//			philo = seat->next;
//			free(temp);
//			i++;
//		}
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
		while (i < number_of_philosophers)
		{
			pthread_mutex_destroy(&seat->fork);
			i++;
		}
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.death);
		pthread_mutex_destroy(&seat->philosopher->restrictions->mutex.write);
	}
}
