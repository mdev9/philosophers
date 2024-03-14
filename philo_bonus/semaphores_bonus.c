/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:00:59 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 09:23:35 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_philos *philos)
{
	if (sem_init(&philos->forks_sem, 0, philos->nb_of_philos) == -1)
	{
		printf("Semaphore initialization failed");
		free_philos(philos);
		exit(EXIT_FAILURE);
	}
	if (sem_init(&philos->write_sem, 0, 1) == -1)
	{
		printf("Semaphore initialization failed");
		free_philos(philos);
		exit(EXIT_FAILURE);
	}
	if (sem_init(&philos->done_sem, 0, 1) == -1)
	{
		printf("Semaphore initialization failed");
		free_philos(philos);
		exit(EXIT_FAILURE);
	}
	if (sem_init(&philos->meal_sem, 0, 1) == -1)
	{
		printf("Semaphore initialization failed");
		free_philos(philos);
		exit(EXIT_FAILURE);
	}
}

void	ft_sem_wait(void *sem)
{
	if (sem_wait(sem) == -1)
	{
		printf("Semaphore wait failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_sem_post(void *sem)
{
	if (sem_post(sem) == -1)
	{
		printf("Semaphore post failed");
		exit(EXIT_FAILURE);
	}
}
