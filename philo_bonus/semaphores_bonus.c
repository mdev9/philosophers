/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:00:59 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/18 11:11:27 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_philos *philos)
{
	sem_unlink("forks_sem");
	sem_unlink("write_sem");
	sem_unlink("done_sem");
	sem_unlink("meal_sem");
	philos->forks_sem = sem_open("forks_sem",
		O_CREAT | O_EXCL, 0644, philos->nb_of_philos);
	philos->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, 0644, 1);
	philos->done_sem = sem_open("done_sem", O_CREAT | O_EXCL, 0644, 1);
	philos->meal_sem = sem_open("meal_sem", O_CREAT | O_EXCL, 0644, 1);
}

void	close_semaphores(t_philo *philo)
{
	sem_close(philo->forks_sem);
	sem_unlink("forks_sem");
	sem_close(philo->write_sem);
	sem_unlink("write_sem");
	sem_close(philo->done_sem);
	sem_unlink("done_sem");
	sem_close(philo->meal_sem);
	sem_unlink("meal_sem");
}
