//
// Created by Diani on 07/08/2021.
//

#include "../includes/philosophers.h"

void	reset_input(t_input *input)
{
	input->number_of_philosophers = -1;
	input->time_to_die = -1;
	input->time_to_eat = -1;
	input->time_to_sleep = -1;
	input->times_must_eat = -1;
}

int	extract_arg(char *arg)
{
	if (ft_is_pos_number(arg))
		return (ft_atoi(arg));
	else
		return (print_error("Argument is not a number or is negative"));
}

int	check_args(t_input input) // revisar si es input.number_of_philos < 1 o es input.number_of_philos < 2
{
	if (input.number_of_philosophers < 1)
		return (print_error("Invalid number of philosophers"));
	if (input.time_to_die <= 0 || input.time_to_eat <= 0
		|| input.time_to_sleep <= 0)
		return (print_error("Invalid value for time"));
	if (input.times_must_eat <= 0) //revisar esta condicion
		return (print_error("Invalid value for times must eat"));
	return (1);
}

int	parsing(char **argv, t_input *input)
{
	reset_input(input);
	input->number_of_philosophers = extract_arg(argv[1]);
	input->time_to_die = extract_arg(argv[2]);
	input->time_to_eat = extract_arg(argv[3]);
	input->time_to_sleep = extract_arg(argv[4]);
	if (argv[5])
		input->times_must_eat = extract_arg(argv[5]);
	else
		input->times_must_eat = 1; //revisar si es necesario
	return (check_args(*input));
}
