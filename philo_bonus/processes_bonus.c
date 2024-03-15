/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/15 08:40:57 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philos_processes(t_philos *philos)
{
	int	i;
	int	pid;

	philos->start_time = get_current_time();
	i = 1;
	while (i <= philos->nb_of_philos)
	{
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
			if (philos->philos[i]->died)
			{
				destroy_semaphores(philos);
				printf("a philo died\n");
				free_philos(philos);
				exit(1);
			}
			destroy_semaphores(philos);
			pthread_join(philos->monitor_thread, 0);
			free_philos(philos);
			exit(0);
		}
		else
			philos->philos[i]->pid = pid;
		i++;
	}
}

void	monitor_death(t_philos *philos)
{
	int i;
	int status;

	i = 1;
	while (i <= philos->nb_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while (i <= philos->nb_of_philos)
			{
				kill(philos->philos[i]->pid, 0);
				printf("killed %d\n", philos->philos[i]->pid);
				i++;
			}
		}
		i++;
	}
}
