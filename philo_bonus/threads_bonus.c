/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 15:56:49 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

void	create_philos_processes(t_philos *philos)
{
	int	i;
	int	pid;

	philos->start_time = get_current_time();
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		//pthread_create(&philos->philos[i]->thread, 0, philo_routine, philos->philos[i]);
		pid = fork();
		if (pid == -1)
		{
			free_philos(philos);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			pthread_create(&philos->monitor_thread, 0, monitor_philo, philos->philos[i]);
			philo_routine(philos->philos[i]);
			pthread_join(philos->monitor_thread, 0);
			destroy_semaphores(philos);
			free_philos(philos);
			exit(0);
		}
		else
			philos->philos[i]->pid = pid;
		i++;
	}
}
