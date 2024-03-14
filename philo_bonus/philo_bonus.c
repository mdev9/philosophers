/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 08:58:37 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	create_threads(philos);
	join_threads(philos);
	destroy_semaphores(philos);
	free_philos(philos);
	return (0);
}
