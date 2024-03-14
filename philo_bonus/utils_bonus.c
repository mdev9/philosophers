/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:19:51 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 08:58:04 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	destroy_semaphores(t_philos *philos)
{
	if (sem_destroy(&philos->forks_sem) == -1) 
	{
        printf("Semaphore destruction failed");
        exit(EXIT_FAILURE);
    }
	if (sem_destroy(&philos->write_sem) == -1) 
	{
        printf("Semaphore destruction failed");
        exit(EXIT_FAILURE);
    }
	if (sem_destroy(&philos->done_sem) == -1) 
	{
        printf("Semaphore destruction failed");
        exit(EXIT_FAILURE);
    }
	if (sem_destroy(&philos->meal_sem) == -1) 
	{
        printf("Semaphore destruction failed");
        exit(EXIT_FAILURE);
    }
	//pthread_mutex_destroy(&philos->done_sem);
	//pthread_mutex_destroy(&philos->meal_sem);
}
