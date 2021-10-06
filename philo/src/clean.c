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
		*table = (*table)->prev;
		free(temp);
	}
}
