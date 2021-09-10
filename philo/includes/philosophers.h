//
// Created by dsalaman on 08/07/2021.
//

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

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	WITH_FORKS = 4,
}	t_status;

typedef struct s_mutex
{
	pthread_mutex_t		write;
	pthread_mutex_t		death;

}				t_mutex;

typedef struct s_restrictions
{
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			times_must_eat;
	unsigned long		simulation_start_time;
	t_mutex		 mutex; //revisar este nombre de variable
}				t_restrictions;

typedef struct s_philosopher
{
	int					id;
	unsigned long		eating_start_time;
	pthread_t			thread;
	t_status			status;
	t_restrictions		*restrictions;
}				t_philosopher;

// circular doubly linked list
typedef struct s_seat
{
	t_philosopher		*philosopher;
	pthread_mutex_t		fork; //revisar si requiere *
	struct s_seat		*next;
	struct s_seat		*prev;
}	t_seat;

typedef struct s_table
{
	t_seat				*seats;
}				t_table;
/*
 * ------------------------- parsing ------------------------------
 */
int				print_error(char *str);
int				extract_arg(char *arg);
int				check_args(t_restrictions input, int number_of_philosophers,
					int check_times_to_eat);
void			reset_input(t_restrictions *input);
int				parsing(char **argv, t_restrictions *input,
					int *number_of_philosophers);

/*
 * ------------------ philo functions ------------------------------
 */

t_philosopher	*create_philosopher(int id, t_restrictions *restrictions,
					unsigned long eating_start_time);
t_seat			*create_seat(t_philosopher *philosopher);
t_seat			*add_philosopher(t_seat **head, t_philosopher *philosopher);
void			*run_simulation(void *arg);
void			take_forks(t_philosopher *philosopher,
					pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void			go_to_eat(t_philosopher *philosopher,
					pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void			go_to_sleep(t_philosopher *philosopher);
void			go_to_think(t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *message);
int				build_philosopher_table(t_restrictions *input, t_table *table,
					int seats_amount);
void			check_philosopher_status(t_table *table);

/*
 * ------------------ time functions ------------------------------
 */

unsigned long	get_time_millisec(void);
void			fix_sleep_accuracy(unsigned long time_to_sleep);
void			action_time(int action_time);

/*
 * ------------------ Utils --------------------------------------
 */

int				ft_is_pos_number(char *str);
int				ft_iswhitespace(char c);
int				ft_atoi(const char *str);

#endif
