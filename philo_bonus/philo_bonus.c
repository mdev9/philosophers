/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/20 11:20:03 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

void kill_processes(t_philos *philos)
{
	int i;

	i = 1;
	while (i <= philos->nb_of_philos)
	{
		if (philos->philos[i]->id != 0)
			kill(philos->philos[i]->id, SIGKILL);
		i++;
	}
}

void	*monitor_death(void *philos)
{
	t_philos *s_philos;

	s_philos = (t_philos *)philos;
	sem_wait(s_philos->dead_sem);
	kill_processes(s_philos);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	death_monitor;
	t_philos	*philos;

	if (parse_args(argc, argv))
		return (1);
	philos = malloc(sizeof(t_philos));
	if (!philos)
		return (1);
	philos->nb_of_philos = ft_atoi(argv[1]);
	if (init_philos(philos, argc, argv))
		return (1);

	pthread_create(&death_monitor, 0, monitor_death, philos);
	create_philos_processes(philos);
	monitor_processes(philos);
	pthread_join(death_monitor, 0);
	close_semaphores(philos->philos[1]);
	free_philos(philos);
	return (0);
}
