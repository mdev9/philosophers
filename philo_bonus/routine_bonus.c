/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:18:10 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 09:06:51 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	//pthread_mutex_lock(philo->r_fork);
	if (sem_wait(philo->forks_sem) == -1) {
        printf("Semaphore wait failed");
        exit(EXIT_FAILURE);
    }

	time_printf(philo, "has taken a fork");
	//pthread_mutex_lock(philo->l_fork);
	if (sem_wait(philo->forks_sem) == -1) {
        printf("Semaphore wait failed");
        exit(EXIT_FAILURE);
    }

	time_printf(philo, "has taken a fork");
	//pthread_mutex_lock(philo->meal_sem);
	if (sem_wait(philo->meal_sem) == -1) {
        printf("Semaphore wait failed");
        exit(EXIT_FAILURE);
    }
	time_printf(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	//thread_mutex_unlock(philo->meal_sem);
	if (sem_post(philo->meal_sem) == -1) {
        printf("Semaphore post failed");
        exit(EXIT_FAILURE);
    }
	ft_usleep(philo->time_to_eat);
	//pthread_mutex_unlock(philo->r_fork);
	if (sem_post(philo->forks_sem) == -1) {
        printf("Semaphore post failed");
        exit(EXIT_FAILURE);
    }
	//pthread_mutex_unlock(philo->l_fork);
	if (sem_post(philo->forks_sem) == -1) {
        printf("Semaphore post failed");
        exit(EXIT_FAILURE);
    }
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

void	*philo_routine(void *philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)philo;
	if (s_philo->id % 2)
		usleep(1500);
	while (1)
	{
		//pthread_mutex_lock(s_philo->done_sem);
		if (sem_wait(s_philo->done_sem) == -1) {
			printf("Semaphore wait failed");
			exit(EXIT_FAILURE);
		}

		if (!*s_philo->is_done)
		{
			//pthread_mutex_unlock(s_philo->done_sem);
			if (sem_post(s_philo->done_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}

			philo_eat(s_philo);
			philo_sleep(s_philo);
			philo_think(s_philo);
		}
		else
		{
			//pthread_mutex_unlock(s_philo->done_sem);
			if (sem_post(s_philo->done_sem) == -1) {
				printf("Semaphore post failed");
				exit(EXIT_FAILURE);
			}
			break ;
		}
	}
	return (0);
}
