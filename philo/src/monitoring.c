/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/29 15:55:28 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_for_death(void *philo)
{
	t_philos		*p;

	p = philo;
	if (!pthread_mutex_lock(&p->data->now_eat_c))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&p->now_eat, NULL);
		pthread_mutex_unlock(&p->data->now_eat_c);
	}
	while ((p->data->max_eat > check_with_mutex(p, 2) || p->data->max_eat == 0))
	{
		if (!!check_with_mutex(p, 1))
			break ;
		if (p->data->time_to_die <= calc_time(check_with_mutex_2(p)))
		{
			write_msg(5, p->nbr_philo, p);
			return (NULL);
		}
	}
	return (NULL);
}

void	waiting_room(int time_to_wait, t_philos *p)
{
	struct timeval	start;

	if (!check_with_mutex(p, 1))
	{
		gettimeofday(&start, NULL);
		while (calc_time(start) < time_to_wait)
			usleep(time_to_wait / 10);
	}
}

int	check_with_mutex(t_philos *p, int check)
{
	int	ret;

	ret = 0;
	if (check == 1)
	{
		if (!pthread_mutex_lock(&p->data->check_dead_c))
		{
			ret = p->data->check_dead;
			pthread_mutex_unlock(&p->data->check_dead_c);
		}
	}
	if (check == 2)
	{
		if (!pthread_mutex_lock(&p->data->now_times_eat_c))
		{
			ret = p->now_times_eat;
			pthread_mutex_unlock(&p->data->now_times_eat_c);
		}
	}
	return (ret);
}

struct timeval	check_with_mutex_2(t_philos *p)
{
	struct timeval	ret;

	ret.tv_sec = 0;
	ret.tv_usec = 0;
	if (!pthread_mutex_lock(&p->data->now_eat_c))
	{
		ret = p->now_eat;
		pthread_mutex_unlock(&p->data->now_eat_c);
	}
	return (ret);
}
