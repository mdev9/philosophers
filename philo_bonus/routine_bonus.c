/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:18:10 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/18 12:52:13 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	/*sem_wait(philo->done_sem);
	if (!philo->is_done)
	{
		printf("jkh\n");
		sem_post(philo->done_sem);
		close_semaphores(philo);
		exit(0);
	}
	sem_post(philo->done_sem);*/
	sem_wait(philo->forks_sem);
	time_printf(philo, "has taken a fork");
	sem_wait(philo->forks_sem);
	time_printf(philo, "has taken a fork");
	sem_wait(philo->meal_sem);
	time_printf(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	sem_post(philo->meal_sem);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
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

void	philo_routine(t_philos *philos, int i)
{
	t_philo	*s_philo;

	s_philo = philos->philos[i];
	if (!s_philo->id % 2)
		ft_usleep(10);
	sem_wait(s_philo->done_sem);
	while (!*s_philo->is_done)
	{
		usleep(500);
		sem_post(s_philo->done_sem);
		philo_eat(s_philo);
		philo_sleep(s_philo);
		philo_think(s_philo);
		sem_wait(s_philo->done_sem);
	}
	sem_post(s_philo->done_sem);
	close_semaphores(s_philo);
	free_philos(philos);
	exit(0);
}
