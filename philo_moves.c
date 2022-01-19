/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 04:12:35 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 06:16:05 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_next_moves(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_a->write_info);
	write_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->p_a->write_info);
	ft_usleep(philo->p_a->sleep);
	pthread_mutex_lock(&philo->p_a->write_info);
	write_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->p_a->write_info);
}

void	philo_moves(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_f);
	pthread_mutex_lock(&philo->p_a->write_info);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->p_a->write_info);
	if (!philo->right_f)
	{
		ft_usleep(philo->p_a->die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_f);
	pthread_mutex_lock(&philo->p_a->write_info);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->p_a->write_info);
	pthread_mutex_lock(&philo->p_a->write_info);
	write_status("is eating\n", philo);
	pthread_mutex_lock(&philo->p_a->time_eat);
	philo->ms_eat = ft_timer();
	pthread_mutex_unlock(&philo->p_a->time_eat);
	pthread_mutex_unlock(&philo->p_a->write_info);
	ft_usleep(philo->p_a->eat);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(&philo->left_f);
	ft_next_moves(philo);
}
