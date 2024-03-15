/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/15 08:24:07 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (parse_args(argc, argv))
		return (1);
	philos = malloc(sizeof(t_philos));
	if (!philos)
		return (1);
	philos->nb_of_philos = ft_atoi(argv[1]);
	if (init_philos(philos, argc, argv))
		return (1);
	create_philos_processes(philos);
	monitor_death(philos);
	destroy_semaphores(philos);
	free_philos(philos);
	return (0);
}
