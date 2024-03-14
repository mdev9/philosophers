/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:16:43 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/14 09:45:17 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_printf(t_philo *philo, char *str)
{
	sem_wait(philo->done_sem);
	if (!*philo->is_done)
	{
		sem_post(philo->done_sem);
		sem_wait(philo->write_sem);
		printf("%ld %d ", (get_current_time() - *(philo->start_time)),
			philo->id);
		printf("%s\n", str);
		sem_post(philo->write_sem);
	}
	else
		sem_post(philo->done_sem);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
