//
// Created by Diani on 14/08/2021.
//

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
