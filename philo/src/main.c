//
// Created by Diani on 13/07/2021.
//

#include "../includes/philosophers.h"


unsigned long get_time_millisec(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

// function to find how many time a philo spends doing an action
void calc_sleep_accuracy(unsigned long time_to_sleep)
{
	unsigned long start_time_sleep;

	start_time_sleep = get_time_millisec();
	while (get_time_millisec() - start_time_sleep < time_to_sleep)
		usleep(10);
}


void reset_input(t_input *input) //revisar si es necesario
{
	input->number_of_philosophers = -1;
	input->time_to_die = -1;
	input->time_to_eat = -1;
	input->time_to_sleep = -1;
	input->times_must_eat = -1;
}

void set_philo(t_philo *philo)
{
	philo->status = ALIVE;
	philo->start_time = get_time_millisec();

}

int extract_arg(char *arg)
{
	if (ft_is_pos_number(arg))
		return (ft_atoi(arg));
	else
		return(print_error("Argument is not a number or is negative"));
}

int check_args(t_input input)
{
	if (input.number_of_philosophers < 2 || input.number_of_philosophers > MAX_PHILO)
		return(print_error("Invalid number of philosophers")); //chequear si el programa debe funcionar con 1 solo filo
	if (input.time_to_die <= 0 || input.time_to_die > MAX_TIME ||
		input.time_to_eat <= 0 || input.time_to_eat > MAX_TIME ||
		input.time_to_sleep <= 0 || input.time_to_sleep > MAX_TIME)
			return(print_error("Invalid value for time"));
	if (input.times_must_eat != -1 && (input.times_must_eat <= 0 ||
		input.times_must_eat > MAX_NUM_EAT))
			return(print_error("Invalid value for times must eat"));
	return (1);
}

int parsing(char **argv, t_input *input)
{
	reset_input(input);

	input->number_of_philosophers = extract_arg(argv[1]);
	input->time_to_die = extract_arg(argv[2]);
	input->time_to_eat = extract_arg(argv[3]);
	input->time_to_sleep = extract_arg(argv[4]);
	if (argv[5])
	{
		input->times_must_eat = extract_arg(argv[5]);
		printf("Prueba, tiene arg 5\n"); //prueba, borrar luego
	}
	return (check_args(*input));
}

int main(int argc, char **argv)
{
	t_input input;

	if (argc < 5 || argc > 6)
		return(print_error("Number of arguments is not correct"));
	else if (parsing(argv, &input) == -1)
		return(print_error("Invalid arguments"));
	printf("listo el pollo\n");
	//init_philo();

	return (0);
}





