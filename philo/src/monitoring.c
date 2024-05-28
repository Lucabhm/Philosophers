/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/28 15:57:27 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_for_death(void *philo)
{
	t_philos		*p;

	p = philo;
	if (!pthread_mutex_lock(&p->data->checker2))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&(p)->now_eat, NULL);
		pthread_mutex_unlock(&p->data->checker2);
	}
	while ((p->data->max_eat > p->now_times_eat || p->data->max_eat == 0))
	{
		if (check_death(p->data))
			break ;
		if (p->data->time_to_die <= calc_time(p->now_eat))
		{
			if (!pthread_mutex_lock(&p->data->dead))
			{
				gettimeofday(&p->now_death, NULL);
				write_msg(5, calc_time(p->start), p->nbr_philo, p);
				pthread_mutex_unlock(&p->data->dead);
			}
			return (NULL);
		}
	}
	return (NULL);
}

void	waiting_room(int time_to_wait, t_philos *p)
{
	struct timeval	start;

	if (!check_death(p->data))
	{
		gettimeofday(&start, NULL);
		while (calc_time(start) < time_to_wait)
			usleep(time_to_wait / 10);
	}
}

int	check_death(t_data *data)
{
	if (!pthread_mutex_lock(&data->checker))
	{
		if (!data->check_dead)
		{
			pthread_mutex_unlock(&data->checker);
			return (0);
		}
		else
			pthread_mutex_unlock(&data->checker);
	}
	return (1);
}
