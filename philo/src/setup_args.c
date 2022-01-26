/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:56:18 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:40 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	reset_input(t_restrictions *input)
{
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

int	check_args(t_restrictions input, int number_of_philosophers,
		int check_times_to_eat)
{
	if (number_of_philosophers < 1)
		return (print_error("Invalid number of philosophers"));
	if (input.time_to_die <= 0 || input.time_to_eat <= 0
		|| input.time_to_sleep <= 0)
		return (print_error("Invalid value for time"));
	if (check_times_to_eat && input.times_must_eat <= 0)
		return (print_error("Invalid value for times must eat"));
	return (SUCCESSFUL);
}

int	parsing(char **argv, t_restrictions *input, int *number_of_philosophers)
{
	int	check_times_to_eat;

	check_times_to_eat = 0;
	reset_input(input);
	*number_of_philosophers = extract_arg(argv[1]);
	input->time_to_die = extract_arg(argv[2]);
	input->time_to_eat = extract_arg(argv[3]);
	input->time_to_sleep = extract_arg(argv[4]);
	if (argv[5])
	{
		input->times_must_eat = extract_arg(argv[5]);
		check_times_to_eat = 1;
	}
	input->eat_control_counter = 0;
	pthread_mutex_init(&input->mutex.write, NULL);
	pthread_mutex_init(&input->mutex.death, NULL);
	return (check_args(*input, *number_of_philosophers, check_times_to_eat));
}
