/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:18:10 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/15 07:48:32 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	//printf("%d wants to eat\n", philo->id);
	//printf("%d waits for a fork\n", philo->id);
	sem_wait(philo->forks_sem);
	//printf("%d is done waiting for a fork\n", philo->id);
	time_printf(philo, "has taken a fork");
	//printf("%d waits for a fork\n", philo->id);
	sem_wait(philo->forks_sem);
	//printf("%d is done waiting for a fork\n", philo->id);
	time_printf(philo, "has taken a fork");
	//printf("%d is waiting for the meal_sem\n", philo->id);
	sem_wait(philo->meal_sem);
	//printf("%d is done waiting for the meal_sem\n", philo->id);
	time_printf(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	sem_post(philo->meal_sem);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	//printf("%d has dropped his forks\n", philo->id);
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
	if (!(s_philo->id % 2))
		ft_usleep(s_philo->time_to_eat / 2);
	sem_wait(s_philo->done_sem);
	while (!*s_philo->is_done)
	{
		sem_post(s_philo->done_sem);
		philo_eat(s_philo);
		philo_sleep(s_philo);
		philo_think(s_philo);
		sem_wait(s_philo->done_sem);
	}
	sem_post(s_philo->done_sem);
	//printf("%d is done with his routine\n", s_philo->id);
	return (0);
}
