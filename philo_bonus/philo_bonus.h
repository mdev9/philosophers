/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:26 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/20 13:00:12 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philo	t_philo;

typedef struct s_philos
{
	int				*is_done;
	struct s_philo	**philos;
	size_t			start_time;
	int				nb_of_philos;
	pthread_t		monitor_thread;
	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*done_sem;
	sem_t			*meal_sem;
	sem_t			*dead_sem;
}				t_philos;

typedef struct s_philo
{
	int			pid;
	int			id;
	int			died;
	int			*is_done;
	int			is_eating;
	int			meals_eaten;
	int			nb_of_philos;
	size_t		last_meal;
	size_t		*start_time;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			nb_times_to_eat;
	sem_t		*forks_sem;
	sem_t		*write_sem;
	sem_t		*done_sem;
	sem_t		*meal_sem;
	sem_t		*dead_sem;
	t_philos	*philos;
}			t_philo;

int		is_digit(int c);
int		ft_atoi(const char *nptr);
int		parse_args(int argc, char **argv);
size_t	get_current_time(void);
void	time_printf(t_philo *philo, char *str);
int		ft_usleep(size_t milliseconds);
void	philo_routine(t_philos *philos, int i);
void	*monitor_philo(void *philo);
int		init_philos(t_philos *philos, int argc, char **argv);
void	create_philos_processes(t_philos *philos);
void	close_semaphores(t_philo *philo);
void	free_philos(t_philos *philos);
void	init_semaphores(t_philos *philos);
void	monitor_processes(t_philos *philos);
int		ft_strlen(char *str);
int		ft_putstr(const char *s);
int		ft_putnbr(long nb);
void	*monitor_death(void *philos);
void	kill_processes(t_philos *philos);

#endif
