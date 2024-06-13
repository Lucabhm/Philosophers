/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/13 14:47:50 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg_thinking(t_philos *p)
{
	const char	*format;

	format = "%ld %i is thinking\n";
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf(format, calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
	if (p->nbr_philo % 2 != 0)
		usleep(500);
}

void	msg_eating(t_philos *p)
{
	const char	*format;

	format = "%ld %i is eating\n";
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf(format, calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_sleeping(t_philos *p)
{
	const char	*format;

	format = "%ld %i is sleeping\n";
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf(format, calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_dead(t_philos *p)
{
	const char	*format;

	format = "%ld %i died\n";
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
	{
		printf(format, calc_time(p), p->nbr_philo);
		pthread_mutex_lock(&p->data->check_dead_c);
		p->data->check_dead = 1;
		pthread_mutex_unlock(&p->data->check_dead_c);
	}
	pthread_mutex_unlock(&p->data->write);
}

void	msg_fork(t_philos *p)
{
	const char	*format;

	format = "%ld %i has taken a fork\n";
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf(format, calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}
