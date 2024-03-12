/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:21:04 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/12 10:50:24 by marde-vr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_is_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	argv_are_int(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!str_is_nb(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Error: not enough arguments\n");
		return (1);
	}
	else if (argc > 6)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	if (!argv_are_int(argc, argv))
	{
		printf("Error: some characters aren't digits\n");
		return (1);
	}
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0 || ft_atoi(argv[3]) == 0
		|| ft_atoi(argv[4]) == 0)
	{
		printf("Error: some values are null\n");
		return (1);
	}
	if (argc == 5 && (ft_atoi(argv[5]) == 0))
		return (1);
	return (0);
}

void	fill_struct(t_philos *philos, int argc, char **argv)
{
	philos->nb_of_philo = ft_atoi(argv[0]);
	philos->time_to_die = ft_atoi(argv[1]);
	philos->time_to_eat = ft_atoi(argv[2]);
	philos->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		philos->nb_of_times_each_philo_must_eat = ft_atoi(argv[4]);
}

int	parse_args(int argc, char **argv, t_philos **philos)
{
	if (check_args(argc, argv))
		return (1);
	philos = malloc(sizeof(philos));
	if (!philos)
		return (1);
	fill_struct(*philos, argc, argv);
	return (0);
}
