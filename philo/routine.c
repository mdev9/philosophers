/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:18:10 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 17:57:01 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
