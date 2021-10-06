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

void	clean_table(t_seat **table)
{
	t_seat	*temp;

	while (*table != NULL)
	{
		temp = *table;
		*table = (*table)->next;
		free(temp);
	}
}

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

/*
 * Tengo que limpiar:
 * 1. philosopher (tabla)
 * 2. seat
 * 3. destroy mutex del fork
 * 4. destroy mutex de death
 * 5. destroy mutex de write
 */