/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 21:11:59 by diani         #+#    #+#                 */
/*   Updated: 2022/02/12 21:11:59 by diani         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
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

/**
 * A for can be FREE if no philosopher is using it,
 * LEFT and RIGHT if a fork is reservation.
 * One philosopher needs both RIGHT and LEFT reservation to be able to eat.
 */
typedef enum e_fork_state
{
	RIGHT,
	LEFT,
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
	bool				allow_write;
	unsigned long		simulation_start_time;
	t_mutex				mutex;
}				t_restrictions;

typedef struct s_reservation
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_fork_state		*left_state;
	t_fork_state		*right_state;
}				t_reservation;

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
	t_fork_state		fork_state;
	struct s_seat		*next;
}	t_seat;

typedef struct s_table
{
	t_seat				*seats;
}				t_table;

/**
 * --------------------------------- parsing ----------------------------------
 */
void			reset_input(t_restrictions *input);
int				extract_arg(char *arg);
int				check_args(t_restrictions input, int number_of_philosophers,
					int check_times_to_eat);
int				parsing(char **argv, t_restrictions *input,
					int *number_of_philosophers);

/**
 * ----------------------------- philo functions ------------------------------
 */
t_philosopher	*create_philosopher(int id, t_restrictions *restrictions,
					unsigned long eating_start_time);
t_seat			*create_seat(t_philosopher *philosopher);
t_seat			*add_philosopher(t_seat **head, t_philosopher *philosopher);
int				build_philosopher_table(t_restrictions *input, t_table *table,
					int seats_amount);
void			*run_simulation(void *arg);
void			take_forks(t_philosopher *philo, t_reservation reservation);
void			go_to_eat(t_philosopher *philo, t_reservation reservation);
void			go_to_sleep(t_philosopher *philosopher);
void			go_to_think(t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *start_color,
					char *message, char *reset_color);
void			check_philosopher_status(t_table *table);
void			change_philosopher_status(t_philosopher *philo, t_status stat);
void			change_fork_state(pthread_mutex_t *fork,
					t_fork_state *fork_state, t_fork_state state);
void			reserve_left(t_reservation *reservation,
					pthread_mutex_t *fork, t_fork_state *state);
void			reserve_right(t_reservation *reservation,
					pthread_mutex_t *fork, t_fork_state *state);
bool			check_enough_meals(t_seat *seat);

/**
 * -----------------------------_ time functions ------------------------------
 */
unsigned long	get_time_millisec(void);
void			action_time(int action_time);

/**
 * ------------------------------- Utils --------------------------------------
 */
int				ft_is_pos_number(char const *str);
int				ft_iswhitespace(char c);
int				ft_atoi(const char *str);
void			clean_seats(t_seat *seat);
void			free_all(t_seat *seat);
int				print_error(char *str);

#endif
