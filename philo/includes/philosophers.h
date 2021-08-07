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
# define MAX_PHILO 1000
# define MAX_TIME 1000000
# define MAX_NUM_EAT 1000

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE,
}	t_action;

typedef  enum e_status
{
	DEAD,
	ALIVE,
} t_status;

typedef struct s_input //lo que puede entrar por consola, max 5 argumentos excl. nombre ejecutable
{
	int number_of_philosophers;
	int	time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int times_must_eat;
}				t_input;

typedef struct	s_philo{
	int				philo_id;
	int				count_eat;
	unsigned long	start_time;
	unsigned long	time_eat;
	pthread_t 		philo_thread;
	pthread_t 		tracking;
	pthread_mutex_t *fork_one;
	pthread_mutex_t *fork_two;
	pthread_mutex_t *death_lock;
	pthread_mutex_t *write_lock;
	t_status		status;
	t_input			*input;
}				t_philo;


int		print_error(char *str);
int extract_arg(char *arg);
int check_args(t_input input);
void	reset_input(t_input *input);
int parsing(char **argv, t_input *input);
int		is_positive_number(int argc, char **argv);
void set_input(t_input *input, char **argv);

// ------------------ time functions ------------------------------

unsigned long get_time_millisec(void);
void calc_sleep_accuracy(unsigned long time_to_sleep);

// ------------------ Utils --------------------------------------

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strtrim(const char *s1, const char *set);
int		ft_ispositive_number(char *str);
int		ft_is_pos_number(char *str);
int		ft_isnumber(char *str);
long	ft_atol(const char *str);
int		ft_iswhitespace(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
int		map_data_to_int(char *str);

#endif
