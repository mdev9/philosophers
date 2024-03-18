/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/18 13:36:41 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	child_process(t_philos *philos, int i)
{
	pthread_create(&philos->monitor_thread,
		0, monitor_philo, philos->philos[i]);
	pthread_detach(philos->monitor_thread);
	philo_routine(philos, i);
	//pthread_join(philos->monitor_thread, 0);
	printf("joined\n");
	close_semaphores(philos->philos[1]);
	/*if (philos->philos[i]->died)
	{
		free_philos(philos);
		exit(1);
	}*/
	free_philos(philos);
	exit(0);
}

void	create_philos_processes(t_philos *philos)
{
	int	i;

	philos->start_time = get_current_time();
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		philos->philos[i]->pid = fork();
		if (philos->philos[i]->pid == -1)
		{
			free_philos(philos);
			exit(EXIT_FAILURE);
		}
		else if (philos->philos[i]->pid == 0)
			child_process(philos, i);
		usleep(1);
		printf("%d\n", philos->philos[i]->pid);
		i++;
	}
}

void	monitor_death(t_philos *philos)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (i <= philos->nb_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while (i <= philos->nb_of_philos)
			{
				kill(philos->philos[i]->pid, SIGKILL);
				i++;
			}
		}
		i++;
	}
}
