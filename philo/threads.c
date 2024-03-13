/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/13 17:21:53 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos_threads(t_philos *philos)
{
	int	i;

	i = 1;
	while (i <= philos->nb_of_philos)
	{
		pthread_create(&philos->philos[i]->thread, 0, philo_routine,
			philos->philos[i]);
		i++;
	}
}

void	create_threads(t_philos *philos)
{
	philos->start_time = get_current_time();
	pthread_create(&philos->monitor_thread, 0, monitor_philos, philos);
	create_philos_threads(philos);
}

void	join_threads(t_philos *philos)
{
	int	i;

	pthread_join(philos->monitor_thread, 0);
	i = 1;
	while (i <= philos->nb_of_philos)
	{
		pthread_join(philos->philos[i]->thread, 0);
		i++;
	}
}
