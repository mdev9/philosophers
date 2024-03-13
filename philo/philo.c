/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 11:12:23 by marde-vr         ###   ########.fr       */
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
	pthread_mutex_lock(philo->write_lock);
	printf("%ld %d ", (get_current_time() - *(philo->start_time)), philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(philo->write_lock);
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
	time_printf(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
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

int	philos_done_eating(t_philos *philos)
{
	int	i;

	i = 1;
	while (philos->philos[i])
	{
		if (philos->philos[i]->nb_times_to_eat != 0) //debug
			printf("meals_eaten by %d: %d/%d\n", i, philos->philos[i]->meals_eaten, philos->philos[i]->nb_times_to_eat); //debug
		if (philos->philos[i]->nb_times_to_eat == 0 || philos->philos[i]->meals_eaten < philos->philos[i]->nb_times_to_eat)
			return (0);
		i++;
	}
	printf("all philos are done eating\n");
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
		{
			time_printf(cur_philo, "died");
			return (1);
		}
		i++;
	}
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
	philo->is_dead = philos->is_dead;
	philo->l_fork = &philos->forks[philo_i - 1];
	if (philo_i == philos->nb_of_philos)
		philo->r_fork = &philos->forks[0];
	else
		philo->r_fork = &philos->forks[philo_i];
	philo->write_lock = &philos->write_lock;
	philo->dead_lock = &philos->dead_lock;
	philo->meal_lock = &philos->meal_lock;
	fill_philo_struct(philo, argc, argv, philo_i);
	return (philo);
}

int	init_philos(t_philos *philos, int argc, char **argv, int nb_of_philos)
{
	philos->philos = malloc(sizeof(t_philo) * (nb_of_philos + 1));
	if (!philos->philos)
	{
		free_philos(philos);
		return (1);
	}

	philos->nb_of_philos = nb_of_philos;
	philos->is_dead = malloc(sizeof(int));
	*(philos->is_dead) = 0;

	pthread_mutex_init(&philos->write_lock, NULL);
	pthread_mutex_init(&philos->dead_lock, NULL);
	pthread_mutex_init(&philos->meal_lock, NULL);

	int	i;
	i = 1;
	while (i <= nb_of_philos)
	{
		philos->philos[i] = init_philo(argc, argv, i, philos);
		if (!philos->philos[i])
		{
			free_philos(philos);
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
	printf("joined all threads\n");
}

void	destroy_mutexes(t_philos *philos)
{
	printf("Destroying mutexes\n");
	int i;
	i = 0;
	while (i < philos->nb_of_philos)
	{
		pthread_mutex_destroy(&philos->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->write_lock);
	pthread_mutex_destroy(&philos->dead_lock);
	pthread_mutex_destroy(&philos->meal_lock);
}

void	*monitor_philos(void *philos)
{
	t_philos *s_philos;
	s_philos = (t_philos *)philos;
	while (!*s_philos->is_dead)
	{
		//printf("is_dead:%d\n", *s_philos->is_dead);
		if ((philos_starving(philos)) || (philos_done_eating(philos)))
			*(s_philos->is_dead) = 1;
	}
	printf("is_dead:%d\n", *s_philos->is_dead);
	return (0);
}

void print_struct(t_philo *philo)
{
    printf("philo: %p\n", (void *)philo);
    printf("philo->id: %d\n", philo->id);
    printf("philo->is_dead: %p\n", (void *)philo->is_dead);
    printf("*philo->is_dead: %d\n", *philo->is_dead);
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
	t_philo *s_philo;
	s_philo = (t_philo *)philo;
	//print_struct(s_philo);
	//printf("is_dead: %d\n", *s_philo->is_dead);
	while (!*s_philo->is_dead)
	{
		philo_eat(s_philo);
		philo_sleep(s_philo);
		philo_think(s_philo);
	}
	return (0);
}

void	create_philos_threads(t_philos *philos)
{
	int i;

	i = 1;
	while (i <= philos->nb_of_philos)
	{
		pthread_create(&philos->philos[i]->thread, 0, philo_routine, philos->philos[i]);
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
	int	nb_of_philos;

	if (parse_args(argc, argv))
		return (1);

	nb_of_philos = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philos));
	if (!philos)
		return (1);

	pthread_mutex_t *forks;
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	int i = 0;
	while (i < philos->nb_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	philos->forks = forks;

	if (init_philos(philos, argc, argv, nb_of_philos))
		return (1);
	

	create_threads(philos);
	join_threads(philos);
	destroy_mutexes(philos);
	free_philos(philos);
	return (0);
}
