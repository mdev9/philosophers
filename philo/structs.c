/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:23:23 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 17:24:10 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
