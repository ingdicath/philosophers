/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 16:09:24 by dsalaman      #+#    #+#                 */
/*   Updated: 2022/01/26 08:08:01 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define ORANGE "\033[38;5;172m"
# define SUCCESSFUL 1
# define FAILURE -1

typedef enum e_status
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	WITH_FORKS,
}	t_status;

typedef enum e_fork_state
{
	BORROWED,
	TAKEN,
	FREE,
}	t_fork_state;

typedef struct s_mutex
{
	pthread_mutex_t		write;
	pthread_mutex_t		death;
}				t_mutex;

typedef struct s_restrictions
{
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					times_must_eat;
	int					eat_control_counter;
	unsigned long		simulation_start_time;
	t_mutex				mutex;
}				t_restrictions;

typedef struct s_philosopher
{
	int					id;
	int					eating_counter;
	unsigned long		eating_start_time;
	pthread_t			thread;
	t_status			status;
	t_restrictions		*restrictions;
}				t_philosopher;

typedef struct s_seat
{
	t_philosopher		*philosopher;
	pthread_mutex_t		fork;
	t_fork_state 		fork_state;//revisar si debe ser apuntador
	struct s_seat		*next;
}	t_seat;

typedef struct s_table
{
	t_seat				*seats;
}				t_table;

/**
 * ------------------------- parsing ------------------------------
 */

int				extract_arg(char *arg);
int				check_args(t_restrictions input, int number_of_philosophers,
					int check_times_to_eat);
void			reset_input(t_restrictions *input);
int				parsing(char **argv, t_restrictions *input,
					int *number_of_philosophers);

/**
 * ------------------ philo functions ------------------------------
 */
t_philosopher	*create_philosopher(int id, t_restrictions *restrictions,
					unsigned long eating_start_time);
t_seat			*create_seat(t_philosopher *philosopher);
t_seat			*add_philosopher(t_seat **head, t_philosopher *philosopher);
void			*run_simulation(void *arg);
void			take_forks(t_seat *seat);
void			go_to_eat(t_seat *seat);
void			go_to_sleep(t_philosopher *philosopher);
void			go_to_think(t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *start_color,
					char *message, char *reset_color);
int				build_philosopher_table(t_restrictions *input, t_table *table,
					int seats_amount);
void			check_philosopher_status(t_table *table, int num_philosophers);
void			eating_control(int num_philos,
					const t_philosopher *curr_philosopher);
unsigned long	get_time_millisec(void);
void			action_time(int action_time);

/**
 * ------------------ Utils --------------------------------------
 */
int				ft_is_pos_number(char const *str);
int				ft_iswhitespace(char c);
int				ft_atoi(const char *str);
void			clean_table(t_seat *seat, int number_of_philosophers);
void			clean_seats(t_seat *seat);
void			clean_mutexes(t_seat *seat, int num_philosophers);
int				print_error(char *str);
#endif
