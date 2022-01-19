/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:17:07 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 06:40:38 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char **argv, int i, int j)
{
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || ft_strlen(argv[i]) > 10)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_check(int argc, char **argv, t_struct *philos)
{
	if ((argc == 5 || argc == 6) && is_int(argv, 1, 0))
	{
		philos->arg.total = ft_atoi(argv[1]);
		philos->arg.die = ft_atoi(argv[2]);
		philos->arg.eat = ft_atoi(argv[3]);
		philos->arg.sleep = ft_atoi(argv[4]);
		philos->arg.x_eat = -1;
		if (argc == 6)
			philos->arg.x_eat = ft_atoi(argv[5]);
		if (philos->arg.total <= 0 || philos->arg.sleep <= 0 \
				|| philos->arg.eat <= 0 || philos->arg.die <= 0)
			return (0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	philos;

	if (!ft_check(argc, argv, &philos))
		return (ft_error("ARGS probleme\n"));
	philos.philo = malloc(sizeof(t_philo) * philos.arg.total);
	if (!philos.philo)
		return (ft_error("MALLOC errors\n"));
	if (!init_value(&philos))
	{
		free(philos.philo);
		return (0);
	}
	if (!create_thread(&philos))
	{
		free(philos.philo);
		return (0);
	}
	this_is_the_end(&philos);
}
