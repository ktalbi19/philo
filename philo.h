/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktalbi <ktalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:03:25 by ktalbi            #+#    #+#             */
/*   Updated: 2022/01/19 06:17:33 by ktalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_arg
{
	int				total;
	int				die;
	int				eat;
	int				sleep;
	int				x_eat;
	long			time_start;
	int				stop;
	int				nb_p_finish;
	pthread_mutex_t	write_info;
	pthread_mutex_t	dead;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finish;
}				t_arg;

typedef struct s_philo
{
	int				id;
	int				eat_x_times;
	pthread_mutex_t	left_f;
	pthread_mutex_t	*right_f;
	t_arg			*p_a;
	long			ms_eat;
	int				finish;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
}				t_philo;

typedef struct s_struct
{
	t_arg			arg;
	t_philo			*philo;
}				t_struct;

//utils
int			ft_atoi(const char *str);
void		write_status(char *str, t_philo *philo);
int			ft_strlen(char *str);
long int	ft_timer(void);
void		ft_usleep(long int time_in_ms);

//threads
int			check_death(t_philo *philo, int i);
void		*is_dead(void *data);
void		*thread(void *data);
int			create_thread(t_struct *philos);

//moves
void		ft_next_moves(t_philo *philo);
void		philo_moves(t_philo *philo);

//main
int			is_int(char **argv, int i, int j);
int			ft_check(int argc, char **argv, t_struct *philos);

//init
void		init_mutex(t_struct *philos);
int			init_value(t_struct *philos);

//errors
int			ft_error(char *str);

//end
int			check_death_2(t_struct *philo);
void		this_is_the_end(t_struct *philos);

#endif