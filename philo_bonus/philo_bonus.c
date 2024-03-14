/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:08:32 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 17:36:59 by marde-vr         ###   ########.fr       */
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
	create_philos_processes(philos);
	
	//sem_post(philos->done_sem);
	//sem_post(philos->meal_sem);
	//sem_post(philos->write_sem);

	int	i;
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
		//free(philos->philos[i]);
		i++;
	}
	destroy_semaphores(philos);
	free_philos(philos);
	return (0);
}
