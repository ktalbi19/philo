/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 02:50:51 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 06:13:55 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->p_a->dead);
	if (i)
		philo->p_a->stop = i;
	if (philo->p_a->stop)
	{
		pthread_mutex_unlock(&philo->p_a->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_a->dead);
	return (0);
}

void	*is_dead(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->p_a->die + 1);
	pthread_mutex_lock(&philo->p_a->time_eat);
	pthread_mutex_lock(&philo->p_a->finish);
	if (!check_death(philo, 0) && !philo->finish && \
		((ft_timer() - philo->ms_eat) >= (long)(philo->p_a->die)))
	{
		pthread_mutex_unlock(&philo->p_a->time_eat);
		pthread_mutex_unlock(&philo->p_a->finish);
		pthread_mutex_lock(&philo->p_a->write_info);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->p_a->write_info);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->p_a->time_eat);
	pthread_mutex_unlock(&philo->p_a->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->p_a->eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, data);
		philo_moves(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->eat_x_times == philo->p_a->x_eat)
		{
			pthread_mutex_lock(&philo->p_a->finish);
			philo->finish = 1;
			philo->p_a->nb_p_finish++;
			if (philo->p_a->nb_p_finish == philo->p_a->total)
			{
				pthread_mutex_unlock(&philo->p_a->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->p_a->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_thread(t_struct *philos)
{
	int	i;

	i = 0;
	while (i < philos->arg.total)
	{
		philos->philo[i].p_a = &philos->arg;
		if (pthread_create(&philos->philo[i].thread_id, NULL,
				thread, &philos->philo[i]) != 0)
			return (ft_error("THREAD error"));
		i++;
	}
	return (1);
}
