/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:21:04 by marde-vr          #+#    #+#             */
/*   Updated: 2024/03/12 15:29:27 by marde-vr         ###   ########.fr       */
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

int	parse_args(int argc, char **argv)
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
	if (argc == 6 && (ft_atoi(argv[5]) == 0))
		return (1);
	return (0);
}

