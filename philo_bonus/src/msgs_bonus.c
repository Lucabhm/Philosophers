/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/06 14:20:50 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	msg_thinking_b(t_philos *p)
{
	long	time;

	time = 0;
	if (!sem_wait(p->data->write))
	{
		time = (get_time_b() - ((p->data->start.tv_sec * 1000)
					+ (p->data->start.tv_usec / 1000)));
		if (!check_with_mutex_b(p, 1))
			printf("%ld %i \e[0;33mis thinking\e[0m\n", time, p->nbr_philo);
		sem_post(p->data->write);
	}
}

void	msg_eating_b(t_philos *p)
{
	long	time;

	time = 0;
	if (!sem_wait(p->data->write))
	{
		time = (get_time_b() - ((p->data->start.tv_sec * 1000)
					+ (p->data->start.tv_usec / 1000)));
		if (!check_with_mutex_b(p, 1))
			printf("%ld %i \e[0;32mis eating\e[0m\n", time, p->nbr_philo);
		sem_post(p->data->write);
	}
}

void	msg_sleeping_b(t_philos *p)
{
	long	time;

	time = 0;
	if (!sem_wait(p->data->write))
	{
		time = (get_time_b() - ((p->data->start.tv_sec * 1000)
					+ (p->data->start.tv_usec / 1000)));
		if (!check_with_mutex_b(p, 1))
			printf("%ld %i \e[0;34mis sleeping\e[0m\n", time, p->nbr_philo);
		sem_post(p->data->write);
	}
}

void	msg_dead_b(t_philos *p)
{
	long	time;

	time = 0;
	if (!sem_wait(p->data->write))
	{
		time = (get_time_b() - ((p->data->start.tv_sec * 1000)
					+ (p->data->start.tv_usec / 1000)));
		if (!check_with_mutex_b(p, 1))
		{
			printf("\033[0;31m%ld %i died\033[0m\n", time, p->nbr_philo);
			if (!sem_wait(p->data->check_dead_c))
			{
				p->data->check_dead = 1;
				
				exit(1);
			}
		}
		sem_post(p->data->write);
	}
}

void	msg_fork_b(t_philos *p)
{
	long	time;

	time = 0;
	if (!sem_wait(p->data->write))
	{
		time = (get_time_b() - ((p->data->start.tv_sec * 1000)
					+ (p->data->start.tv_usec / 1000)));
		if (!check_with_mutex_b(p, 1))
			printf("%ld %i has taken a fork\n", time, p->nbr_philo);
		sem_post(p->data->write);
	}
}
