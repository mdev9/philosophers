/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 09:10:09 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_done_eating(t_philo *philo)
{
	if (!philo->is_eating)
	{
		if (philo->nb_times_to_eat == 0
			|| philo->meals_eaten < philo->nb_times_to_eat)
		{
			//pthread_mutex_unlock(philo->meal_sem);
			if (sem_post(philo->meal_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}

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
			//pthread_mutex_lock(&philos->meal_sem);
			if (sem_wait(&philos->meal_sem) == -1) {
				printf("Semaphore wait failed");
				exit(EXIT_FAILURE);
			}

			if (philos->philos[i]->meals_eaten
				>= philos->philos[i]->nb_times_to_eat)
				nb_of_philos_done_eating++;
			//pthread_mutex_unlock(&philos->meal_sem);
			if (sem_post(&philos->meal_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
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
	//pthread_mutex_lock(&philos->meal_sem);
    if (sem_wait(&philos->meal_sem) == -1) {
        printf("Semaphore wait failed");
        exit(EXIT_FAILURE);
    }
	while (i <= philos->nb_of_philos)
	{
		cur_philo = philos->philos[i];
		if (cur_philo->last_meal == 0)
			cur_philo->last_meal = *cur_philo->start_time;
		if (get_current_time() - cur_philo->last_meal >= cur_philo->time_to_die)
		{
			//pthread_mutex_unlock(&philos->meal_sem);
			if (sem_post(&philos->meal_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
			time_printf(cur_philo, "died");
			
			//pthread_mutex_unlock(cur_philo->r_fork);
			if (sem_post(&philos->forks_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
			return (1);
		}
		i++;
	}
	//pthread_mutex_unlock(&philos->meal_sem);
	if (sem_post(&philos->meal_sem) == -1) {
		printf("Semaphore post failed");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	*monitor_philos(void *philos)
{
	t_philos	*s_philos;

	s_philos = (t_philos *)philos;
	while (!*s_philos->is_done)
	{
		//pthread_mutex_lock(&s_philos->done_sem);
		if (sem_wait(&s_philos->done_sem) == -1) {
			printf("Semaphore wait failed");
			exit(EXIT_FAILURE);
		}
		if (!*s_philos->is_done)
		{
			//pthread_mutex_unlock(&s_philos->done_sem);
			if (sem_post(&s_philos->done_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
			usleep(100);
			if ((philos_starving(philos)) || (philos_done_eating(philos)))
			{
				//pthread_mutex_lock(&s_philos->done_sem);
				if (sem_wait(&s_philos->done_sem) == -1) {
					printf("Semaphore wait failed");
					exit(EXIT_FAILURE);
				}
				*(s_philos->is_done) = 1;
				//pthread_mutex_unlock(&s_philos->done_sem);
				if (sem_post(&s_philos->done_sem) == -1) {
					printf("Semaphore post failed");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			//pthread_mutex_unlock(&s_philos->done_sem);
			if (sem_post(&s_philos->done_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
			break ;
		}
	}
	return (0);
}
