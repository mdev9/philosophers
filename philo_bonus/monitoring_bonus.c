/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/20 12:59:33 by marde-vr         ###   ########.fr       */
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
			sem_post(philo->meal_sem);
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

int	philo_done_eating(t_philo *philo)
{
	if (philo->nb_times_to_eat != 0)
	{
		sem_wait(philo->meal_sem);
		if (philo->meals_eaten
			>= philo->nb_times_to_eat)
		{
			sem_post(philo->meal_sem);
			return (1);
		}
		sem_post(philo->meal_sem);
	}
	return (0);
}

int	philo_starving(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	if (philo->last_meal == 0)
		philo->last_meal = *philo->start_time;
	if (get_current_time() - philo->last_meal >= philo->time_to_die)
	{
		sem_post(philo->meal_sem);
		time_printf(philo, "died");
		if (philo->nb_of_philos == 1)
			sem_post(philo->forks_sem);
		return (1);
	}
	sem_post(philo->meal_sem);
	return (0);
}

void	*monitor_philo(void *philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)philo;
	while (1)
	{
		ft_usleep(1);
		if (philo_starving(philo))
		{
			sem_wait(s_philo->done_sem);
			*(s_philo->is_done) = 1;
			sem_post(s_philo->done_sem);
			s_philo->died = 1;
			sem_post(s_philo->dead_sem);
			break ;
		}
		if (philo_done_eating(philo))
		{
			sem_wait(s_philo->done_sem);
			*(s_philo->is_done) = 1;
			sem_post(s_philo->done_sem);
			break ;
		}
	}
	return (0);
}

void	*monitor_death(void *philos)
{
	t_philos	*s_philos;

	s_philos = (t_philos *)philos;
	sem_wait(s_philos->dead_sem);
	kill_processes(s_philos);
	return (0);
}
