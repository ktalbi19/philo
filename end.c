/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 05:23:24 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 06:39:27 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_2(t_struct *philo)
{
	pthread_mutex_lock(&philo->arg.dead);
	if (philo->arg.stop)
	{
		pthread_mutex_unlock(&philo->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg.dead);
	return (0);
}

void	this_is_the_end(t_struct *philos)
{
	int	i;

	i = -1;
	while (!check_death_2(philos))
		ft_usleep(1);
	while (++i < philos->arg.total)
		pthread_join(philos->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&philos->arg.write_info);
	i = -1;
	while (++i < philos->arg.total)
		pthread_mutex_destroy(&philos->philo[i].left_f);
	if (philos->arg.stop == 2)
		printf("Each philosophers ate %d times\n", philos->arg.x_eat);
	free(philos->philo);
}
