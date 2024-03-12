#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>


typedef struct	s_philos
{
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_of_times_each_philo_must_eat;
}				t_philos;

int		is_digit(int c);
int		ft_atoi(const char *nptr);
int		str_is_nb(char *str);
int		argv_are_int(int argc, char **argv);
int		check_args(int argc, char **argv);
void	fill_struct(t_philos *philo, int argc, char **argv);
int		parse_args(int argc, char **argv, t_philos **philo);

#endif

