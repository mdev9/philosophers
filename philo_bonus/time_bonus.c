/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:16:43 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/20 09:29:37 by marde-vr         ###   ########.fr       */
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
	size_t	time;

	time = (get_current_time() - *(philo->start_time));
	sem_wait(philo->write_sem);
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, " ", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	sem_post(philo->write_sem);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
