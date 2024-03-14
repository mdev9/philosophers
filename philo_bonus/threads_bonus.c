/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 11:18:34 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>

void	create_philos_threads(t_philos *philos)
{
	int	i;
	int	pid;

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
			philo_routine(philos->philos[i]);
			break;
		}
		else
			philos->philos[i]->pid = pid;
		i++;
	}
}

void	create_threads(t_philos *philos)
{
	philos->start_time = get_current_time();
	pthread_create(&philos->monitor_thread, 0, monitor_philos, philos);
	create_philos_threads(philos);
}

void	join_threads(t_philos *philos) //useless?
{
	int	i;

	pthread_join(philos->monitor_thread, 0);
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		kill(philos->philos[i]->pid, 9);
		//free(philos->philos[i]);
		i++;
	}
}
