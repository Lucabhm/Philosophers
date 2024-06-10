/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/10 12:32:51 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg_thinking(t_philos *p)
{
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf("%ld %i is thinking\n", calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_eating(t_philos *p)
{
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf("%ld %i is eating\n", calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_sleeping(t_philos *p)
{
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf("%ld %i is sleeping\n", calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_dead(t_philos *p)
{
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
	{
		printf("%ld %i died\n", calc_time(p), p->nbr_philo);
		pthread_mutex_lock(&p->data->check_dead_c);
		p->data->check_dead = 1;
		pthread_mutex_unlock(&p->data->check_dead_c);
	}
	pthread_mutex_unlock(&p->data->write);
}

void	msg_fork(t_philos *p)
{
	pthread_mutex_lock(&p->data->write);
	if (!check_with_mutex(p, 1))
		printf("%ld %i has taken a fork\n", calc_time(p), p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}
