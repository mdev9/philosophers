/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:19:51 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 17:25:35 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	count;

	i = 0;
	sign = 1;
	count = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		count *= 10;
		count += (nptr[i] - 48);
		i++;
	}
	return (count * sign);
}

void	destroy_mutexes(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->nb_of_philos)
	{
		pthread_mutex_destroy(&philos->fork_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->write_lock);
	pthread_mutex_destroy(&philos->done_lock);
	pthread_mutex_destroy(&philos->meal_lock);
}
