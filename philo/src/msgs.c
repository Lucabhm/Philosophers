/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/07 16:10:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg_thinking(t_philos *p)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&p->data->write);
	time = (get_time() - ((p->data->start.tv_sec * 1000)
				+ (p->data->start.tv_usec / 1000)));
	if (!check_with_mutex(p, 1))
		printf("%ld %i \e[0;33mis thinking\e[0m\n", time, p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_eating(t_philos *p)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&p->data->write);
	time = (get_time() - ((p->data->start.tv_sec * 1000)
				+ (p->data->start.tv_usec / 1000)));
	if (!check_with_mutex(p, 1))
		printf("%ld %i \e[0;32mis eating\e[0m\n", time, p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_sleeping(t_philos *p)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&p->data->write);
	time = (get_time() - ((p->data->start.tv_sec * 1000)
				+ (p->data->start.tv_usec / 1000)));
	if (!check_with_mutex(p, 1))
		printf("%ld %i \e[0;34mis sleeping\e[0m\n", time, p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}

void	msg_dead(t_philos *p)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&p->data->write);
	time = (get_time() - ((p->data->start.tv_sec * 1000)
				+ (p->data->start.tv_usec / 1000)));
	if (!check_with_mutex(p, 1))
	{
		printf("\033[0;31m%ld %i died\033[0m\n", time, p->nbr_philo);
		pthread_mutex_lock(&p->data->check_dead_c);
		p->data->check_dead = 1;
		pthread_mutex_unlock(&p->data->check_dead_c);
	}
	pthread_mutex_unlock(&p->data->write);
}

void	msg_fork(t_philos *p)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&p->data->write);
	time = (get_time() - ((p->data->start.tv_sec * 1000)
				+ (p->data->start.tv_usec / 1000)));
	if (!check_with_mutex(p, 1))
		printf("%ld %i has taken a fork\n", time, p->nbr_philo);
	pthread_mutex_unlock(&p->data->write);
}
