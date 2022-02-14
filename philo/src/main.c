/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:10:39 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:10:39 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_restrictions	restrictions;
	t_table			table;
	int				number_of_philosophers;

	if (argc < 5 || argc > 6)
		return (print_error("Number of arguments is not correct"));
	else if (parsing(argv, &restrictions, &number_of_philosophers) == FAILURE)
		return (print_error("Invalid arguments"));
	table.seats = NULL;
	printf("%stime(ms)\tphilo\taction%s\n", CYAN, RESET);
	if (build_philosopher_table(&restrictions, &table, number_of_philosophers)
		!= SUCCESSFUL)
		return (print_error("Error building philosophers"));
	check_philosopher_status(&table);
	return (0);
}
