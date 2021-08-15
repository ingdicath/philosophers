//
// Created by Diani on 14/08/2021.
//

#include "../includes/philosophers.h"

void	clean_table(t_node **table)
{
	t_node	*temp;

	while (*table != NULL)
	{
		temp = *table;
		*table = (*table)->prev;
		free(temp);
	}
}
