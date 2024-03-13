#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				*is_dead;
	int				is_eating;
	int				meals_eaten;
	int				nb_of_philos;
	size_t			last_meal;
	size_t			*start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}				t_philo;

typedef struct	s_philos
{
	int				*is_dead;
	t_philo			**philos;
	size_t			start_time;
	int				nb_of_philos;
	pthread_t		monitor_thread;
	pthread_mutex_t *forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}				t_philos;

int		is_digit(int c);
int		ft_atoi(const char *nptr);
int		str_is_nb(char *str);
int		argv_are_int(int argc, char **argv);
int		check_args(int argc, char **argv);
int		parse_args(int argc, char **argv);

#endif

