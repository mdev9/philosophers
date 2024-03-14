/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:06 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 09:21:50 by marde-vr         ###   ########.fr       */
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
			ft_sem_post(philo->meal_sem);
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
			ft_sem_wait(&philos->meal_sem);
			if (philos->philos[i]->meals_eaten
				>= philos->philos[i]->nb_times_to_eat)
				nb_of_philos_done_eating++;
			ft_sem_post(&philos->meal_sem);
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
	ft_sem_wait(&philos->meal_sem);
	while (i <= philos->nb_of_philos)
	{
		cur_philo = philos->philos[i];
		if (cur_philo->last_meal == 0)
			cur_philo->last_meal = *cur_philo->start_time;
		if (get_current_time() - cur_philo->last_meal >= cur_philo->time_to_die)
		{
			ft_sem_post(&philos->meal_sem);
			time_printf(cur_philo, "died");
			ft_sem_post(cur_philo->forks_sem);
			return (1);
		}
		i++;
	}
	ft_sem_post(&philos->meal_sem);
	return (0);
}

void	*monitor_philos(void *philos)
{
	t_philos	*s_philos;

	s_philos = (t_philos *)philos;
	while (!*s_philos->is_done)
	{
		ft_sem_wait(&s_philos->done_sem);
		if (!*s_philos->is_done)
		{
			ft_sem_post(&s_philos->done_sem);
			usleep(100);
			if ((philos_starving(philos)) || (philos_done_eating(philos)))
			{
				ft_sem_wait(&s_philos->done_sem);
				*(s_philos->is_done) = 1;
				ft_sem_post(&s_philos->done_sem);
			}
		}
		else
		{
			ft_sem_post(&s_philos->done_sem);
			break ;
		}
	}
	return (0);
}
