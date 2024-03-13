/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 18:00:24 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_unlock(cur_philo->r_fork);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->meal_lock);
	return (0);
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
