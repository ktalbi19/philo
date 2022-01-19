/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:50:28 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 05:05:13 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_struct *philos)
{
	pthread_mutex_init(&philos->arg.write_info, NULL);
	pthread_mutex_init(&philos->arg.finish, NULL);
	pthread_mutex_init(&philos->arg.time_eat, NULL);
	pthread_mutex_init(&philos->arg.dead, NULL);
}

int	init_value(t_struct *philos)
{
	int	i;

	i = 0;
	philos->arg.time_start = ft_timer();
	philos->arg.stop = 0;
	philos->arg.nb_p_finish = 0;
	init_mutex(philos);
	while (i < philos->arg.total)
	{
		philos->philo[i].id = i + 1;
		philos->philo[i].ms_eat = philos->arg.time_start;
		philos->philo[i].eat_x_times = 0;
		philos->philo[i].right_f = NULL;
		philos->philo[i].finish = 0;
		pthread_mutex_init(&philos->philo[i].left_f, NULL);
		if (philos->arg.total == 1)
			return (1);
		if (i == philos->arg.total - 1)
			philos->philo[i].right_f = &philos->philo[0].left_f;
		else
			philos->philo[i].right_f = &philos->philo[i + 1].left_f;
		i++;
	}
	return (1);
}
