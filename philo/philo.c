/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 17:07:20 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
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
	pthread_mutex_lock(philo->done_lock);
	if (!*philo->is_done)
	{
		pthread_mutex_unlock(philo->done_lock);
		pthread_mutex_lock(philo->write_lock);
		printf("%ld %d ", (get_current_time() - *(philo->start_time)),
			philo->id);
		printf("%s\n", str);
		pthread_mutex_unlock(philo->write_lock);
	}
	else
		pthread_mutex_unlock(philo->done_lock);
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
	pthread_mutex_lock(philo->r_fork);
	time_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	time_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	time_printf(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	time_printf(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	time_printf(philo, "is thinking");
}

int	is_done_eating(t_philo *philo)
{
	if (!philo->is_eating)
	{
		if (philo->nb_times_to_eat == 0
			|| philo->meals_eaten < philo->nb_times_to_eat)
		{
			pthread_mutex_unlock(philo->meal_lock);
			return (0);
		}
	}
	else
	{
		ft_usleep(philo->time_to_eat / 4);
		return (is_done_eating(philo));
	}
	return (1);
}

int	philos_done_eating(t_philos *philos)
{
	int	i;
	int	nb_of_philos_done_eating;

	i = 1;
	nb_of_philos_done_eating = 0;
	while (i <= philos->nb_of_philos)
	{
		if (philos->philos[i]->nb_times_to_eat != 0)
		{
			pthread_mutex_lock(&philos->meal_lock);
			if (philos->philos[i]->meals_eaten
				>= philos->philos[i]->nb_times_to_eat)
				nb_of_philos_done_eating++;
			pthread_mutex_unlock(&philos->meal_lock);
		}
		else
			return (0);
		i++;
	}
	if (nb_of_philos_done_eating == philos->nb_of_philos)
		return (1);
	return (0);
}

int	philos_starving(t_philos *philos)
{
	int		i;
	t_philo	*cur_philo;

	i = 1;
	pthread_mutex_lock(&philos->meal_lock);
	while (i <= philos->nb_of_philos)
	{
		cur_philo = philos->philos[i];
		if (cur_philo->last_meal == 0)
			cur_philo->last_meal = *cur_philo->start_time;
		if (get_current_time() - cur_philo->last_meal >= cur_philo->time_to_die)
		{
			pthread_mutex_unlock(&philos->meal_lock);
			time_printf(cur_philo, "died");
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->meal_lock);
	return (0);
}

void	fill_philo_struct(t_philo *philo, int argc, char **argv, int philo_i)
{
	philo->id = philo_i;
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
	int	i;

	free(philos->is_done);
	free(philos->fork_locks);
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		free(philos->philos[i]);
		i++;
	}
	free(philos->philos);
	free(philos);
}

t_philo	*init_philo(int argc, char **argv, int philo_i, t_philos *philos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (philo);
	philo->start_time = &(philos->start_time);
	philo->is_done = philos->is_done;
	philo->l_fork = &philos->fork_locks[philo_i - 1];
	if (philo_i == philos->nb_of_philos)
		philo->r_fork = &philos->fork_locks[0];
	else
		philo->r_fork = &philos->fork_locks[philo_i];
	philo->write_lock = &philos->write_lock;
	philo->done_lock = &philos->done_lock;
	philo->meal_lock = &philos->meal_lock;
	fill_philo_struct(philo, argc, argv, philo_i);
	return (philo);
}

int	init_forks(t_philos *philos)
{
	int	i;

	philos->fork_locks = malloc(sizeof(pthread_mutex_t) * philos->nb_of_philos);
	if (!philos->fork_locks)
		return (1);
	i = 0;
	while (i < philos->nb_of_philos)
	{
		pthread_mutex_init(&philos->fork_locks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_philos *philos, int argc, char **argv)
{
	int	i;

	init_forks(philos);
	philos->philos = malloc(sizeof(t_philo) * (philos->nb_of_philos + 1));
	if (!philos->philos)
	{
		free_philos(philos);
		return (1);
	}
	philos->is_done = malloc(sizeof(int));
	*(philos->is_done) = 0;
	pthread_mutex_init(&philos->write_lock, NULL);
	pthread_mutex_init(&philos->done_lock, NULL);
	pthread_mutex_init(&philos->meal_lock, NULL);
	i = 0;
	while (++i <= philos->nb_of_philos)
	{
		philos->philos[i] = init_philo(argc, argv, i, philos);
		if (!philos->philos[i])
		{
			free_philos(philos);
			return (1);
		}
	}
	return (0);
}

void	join_threads(t_philos *philos)
{
	int	i;

	pthread_join(philos->monitor_thread, 0);
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		pthread_join(philos->philos[i]->thread, 0);
		i++;
	}
}

void	destroy_mutexes(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->nb_of_philos)
	{
		pthread_mutex_destroy(&philos->fork_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->write_lock);
	pthread_mutex_destroy(&philos->done_lock);
	pthread_mutex_destroy(&philos->meal_lock);
}

void	*monitor_philos(void *philos)
{
	t_philos	*s_philos;

	s_philos = (t_philos *)philos;
	while (!*s_philos->is_done)
	{
		pthread_mutex_lock(&s_philos->done_lock);
		if (!*s_philos->is_done)
		{
			pthread_mutex_unlock(&s_philos->done_lock);
			usleep(100);
			if ((philos_starving(philos)) || (philos_done_eating(philos)))
			{
				pthread_mutex_lock(&s_philos->done_lock);
				*(s_philos->is_done) = 1;
				pthread_mutex_unlock(&s_philos->done_lock);
			}
		}
		else
		{
			pthread_mutex_unlock(&s_philos->done_lock);
			break ;
		}
	}
	return (0);
}

void	print_struct(t_philo *philo)
{
	printf("philo: %p\n", (void *)philo);
	printf("philo->id: %d\n", philo->id);
	printf("philo->is_done: %p\n", (void *)philo->is_done);
	printf("*philo->is_done: %d\n", *philo->is_done);
	printf("philo->is_eating: %d\n", philo->is_eating);
	printf("philo->meals_eaten: %d\n", philo->meals_eaten);
	printf("philo->nb_of_philos: %d\n", philo->nb_of_philos);
	printf("philo->last_meal: %zu\n", philo->last_meal);
	printf("philo->start_time: %p\n", (void *)philo->start_time);
	if (philo->start_time)
		printf("*philo->start_time: %zu\n", *philo->start_time);
	printf("philo->time_to_die: %zu\n", philo->time_to_die);
	printf("philo->time_to_eat: %zu\n", philo->time_to_eat);
	printf("philo->time_to_sleep: %zu\n", philo->time_to_sleep);
	printf("philo->nb_times_to_eat: %d\n", philo->nb_times_to_eat);
}

void	*philo_routine(void *philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)philo;
	if (s_philo->id % 2)
		usleep(1500);
	while (1)
	{
		pthread_mutex_lock(s_philo->done_lock);
		if (!*s_philo->is_done)
		{
			pthread_mutex_unlock(s_philo->done_lock);
			philo_eat(s_philo);
			philo_sleep(s_philo);
			philo_think(s_philo);
		}
		else
		{
			pthread_mutex_unlock(s_philo->done_lock);
			break ;
		}
	}
	return (0);
}

void	create_philos_threads(t_philos *philos)
{
	int	i;

	i = 1;
	while (i <= philos->nb_of_philos)
	{
		pthread_create(&philos->philos[i]->thread, 0, philo_routine,
			philos->philos[i]);
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
	philos = malloc(sizeof(t_philos));
	if (!philos)
		return (1);
	philos->nb_of_philos = ft_atoi(argv[1]);
	if (init_philos(philos, argc, argv))
		return (1);
	create_threads(philos);
	join_threads(philos);
	destroy_mutexes(philos);
	free_philos(philos);
	return (0);
}
