/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/07 16:10:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_for_death(void *philo)
{
	t_philos	*p;

	p = philo;
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex(p, 2))
	{
		if (check_with_mutex(p, 1))
			break ;
		if (p->data->time_to_die <= (get_time() - check_with_mutex_2(p)))
		{
			msg_dead(p);
			return (NULL);
		}
		p = p->next;
	}
	return (NULL);
}

void	waiting_room(int time_to_wait, t_philos *p)
{
	struct timeval	now_time;

	if (!check_with_mutex(p, 1))
	{
		gettimeofday(&now_time, NULL);
		while ((get_time() - ((now_time.tv_sec * 1000)
					+ (now_time.tv_usec / 1000))) < time_to_wait)
			usleep(100);
	}
}

void	waiting_room_m(int time_to_wait, t_philos *p)
{
	struct timeval	now_time;

	if (!check_with_mutex(p, 1))
	{
		gettimeofday(&now_time, NULL);
		while (((get_time() - ((now_time.tv_sec * 1000)
					+ (now_time.tv_usec / 1000))) * 1000) < time_to_wait)
			usleep(50);
	}
}

int	check_with_mutex(t_philos *p, int check)
{
	int	ret;

	ret = 0;
	if (check == 1)
	{
		pthread_mutex_lock(&p->data->check_dead_c);
		ret = p->data->check_dead;
		pthread_mutex_unlock(&p->data->check_dead_c);
	}
	if (check == 2)
	{
		pthread_mutex_lock(&p->now_times_eat_c);
		ret = p->now_times_eat;
		pthread_mutex_unlock(&p->now_times_eat_c);
	}
	return (ret);
}

long	check_with_mutex_2(t_philos *p)
{
	long	ret;

	ret = 0;
	pthread_mutex_lock(&p->now_eat_lock);
	if (p->now_eat.tv_sec == 0)
		gettimeofday(&p->now_eat, NULL);
	ret = (p->now_eat.tv_sec * 1000 + p->now_eat.tv_usec / 1000);
	pthread_mutex_unlock(&p->now_eat_lock);
	return (ret);
}
