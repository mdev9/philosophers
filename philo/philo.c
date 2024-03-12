/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/12 17:15:34 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_printf(t_philo *philo, char *str)
{
	printf("%ld %d ", (get_current_time() - *(philo->start_time)), philo->id);
	printf("%s\n", str);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	//lock right fork mutex
	time_printf(philo, "has taken a fork");
	//lock left fork mutex
	time_printf(philo, "has taken a fork");
	//change variables and lock
	time_printf(philo, "is eating");
	usleep(philo->time_to_eat);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	//drop and unlock both forks
}

void	philo_sleep(t_philo *philo)
{
	time_printf(philo, "is sleeping");
	usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	time_printf(philo, "is thinking");
}


int	philos_done_eating(t_philos *philos)
{
	int	i;

	i = 1;
	while (philos->philos[i])
	{
		if (philos->philos[i]->meals_eaten < philos->philos[i]->nb_times_to_eat)
			return (0);
		i++;
	}
	return (1);
}

int	philos_starving(t_philos *philos)
{
	int i;
	t_philo *cur_philo;

	i = 1;
	while (philos->philos[i])
	{
		cur_philo = philos->philos[i];
		if (cur_philo->time_to_die
			>= (*(cur_philo->start_time) - cur_philo->last_meal))
			return (1);
		i++;
	}
	return (0);
}


void	fill_philo_struct(t_philo *philo, int argc, char **argv, int philo_i)
{
	philo->id = philo_i;
	philo->is_dead = 0;
	philo->is_eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->nb_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_times_to_eat = ft_atoi(argv[5]);
	else
		philo->nb_times_to_eat = 0;
}

void	free_philos(t_philos *philos)
{
	if (philos)
	{
		//todo: free all the philos;
		free(philos);
	}
}

t_philo	*init_philo(int argc, char **argv, int philo_i, t_philos *philos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (philo);
	philo->start_time = &(philos->start_time);
	philo->is_dead = &(philos->is_dead);
	fill_philo_struct(philo, argc, argv, philo_i);
	return (philo);
}

int	init_philos(t_philos **philos, int argc, char **argv)
{
	int	nb_of_philos;
	int	i;

	nb_of_philos = ft_atoi(argv[1]);
	*philos = malloc(sizeof(philos));
	if (!*philos)
		return (1);
	(*philos)->philos = malloc(sizeof(t_philo) * (nb_of_philos + 1));
	if (!(*philos)->philos)
	{
		free_philos(*philos);
		return (1);
	}
	i = 1;
	(*philos)->nb_of_philos = nb_of_philos;
	while (i <= nb_of_philos)
	{
		(*philos)->philos[i] = init_philo(argc, argv, i, *philos);
		if (!(*philos)->philos[i])
		{
			free_philos(*philos);
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_philos *philos)
{
	pthread_join(philos->monitor_thread, 0);
	int i;
	i = 1;
	while (philos->philos[i])
	{
		pthread_join(philos->philos[i]->thread, 0);
		i++;
	}
}

void	*monitor_philos(void *philos)
{
	t_philos *s_philos;
	s_philos = (t_philos *)philos;
	while (!s_philos->is_dead)
	{
		if ((philos_starving(philos)) || (philos_done_eating(philos)))
			s_philos->is_dead = 1;
	}
	//destroy all mutexes
	//free all allocated memory (structs)
	join_threads(philos);
	printf("joined all threads\n");
	return (0);
}

void	*philo_routine(void *philo)
{
	t_philo *s_philo;
	s_philo = (t_philo *)philo;
	while (!s_philo->is_dead)
	{
		philo_eat(s_philo);
		philo_sleep(s_philo);
		philo_think(s_philo);
	}
	time_printf(s_philo, "died");
	return (0);
}

void	create_philos_threads(t_philos *philos)
{
	int i;

	i = 1;
	while (philos->philos[i])
	{
		pthread_create(&philos->philos[i]->thread, 0, philo_routine, &philos->philos[i]);
		i++;
	}
}

void	create_threads(t_philos *philos)
{
	philos->start_time = get_current_time();
	pthread_create(&philos->monitor_thread, 0, monitor_philos, philos);
	create_philos_threads(philos);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (parse_args(argc, argv))
		return (1);
	if (init_philos(&philos, argc, argv))
		return (1);
	
	pthread_mutex_t **lock_array;
	lock_array = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	create_threads(philos);
	return (0);
}
