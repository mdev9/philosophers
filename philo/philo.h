/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:26 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 16:47:51 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				*is_done;
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
	pthread_mutex_t	*done_lock;
	pthread_mutex_t	*meal_lock;
}				t_philo;

typedef struct s_philos
{
	int				*is_done;
	t_philo			**philos;
	size_t			start_time;
	int				nb_of_philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	done_lock;
	pthread_mutex_t	meal_lock;
}				t_philos;

int		is_digit(int c);
int		ft_atoi(const char *nptr);
int		str_is_nb(char *str);
int		argv_are_int(int argc, char **argv);
int		check_args(int argc, char **argv);
int		parse_args(int argc, char **argv);

#endif
