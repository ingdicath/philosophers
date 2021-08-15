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

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	WITH_FORKS = 4,
}	t_status;

typedef struct s_input
{
	int	number_of_philosophers;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	times_must_eat;
}				t_input;

typedef struct s_philosopher
{
	int					id;
	t_status			status;
	struct timeval		eating_start_time;
	pthread_t			thread;

}				t_philosopher;

// circular doubly linked list
typedef struct s_node
{
	t_philosopher		*philosopher;
	pthread_mutex_t		*fork;
	struct s_node		*next;
	struct s_node		*prev;
}	t_node;

/*
 * ------------------------- parsing ------------------------------
 */
int				print_error(char *str);
int				extract_arg(char *arg);
int				check_args(t_input input);
void			reset_input(t_input *input);
int				parsing(char **argv, t_input *input);
int				is_positive_number(int argc, char **argv);
void			set_input(t_input *input, char **argv);

/*
 * ------------------ philo functions ------------------------------
 */

t_philosopher	*create_philosopher(int id, struct timeval eating_start_time);
t_node			*create_node(t_philosopher *philosopher);
t_node			*add_philosopher(t_node **head, t_philosopher *philosopher);
void			*start_simulation(void *arg);
/*
 * ------------------ time functions ------------------------------
 */

unsigned long	get_time_millisec(void);
void			fix_sleep_accuracy(unsigned long time_to_sleep);

/*
 * ------------------ Utils --------------------------------------
 */

int				ft_is_pos_number(char *str);
int				ft_iswhitespace(char c);
int				ft_atoi(const char *str);

#endif
