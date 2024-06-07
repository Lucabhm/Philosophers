/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:43:45 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/07 11:17:36 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*check_for_death_b(void *data)
{
	t_data	*d;

	d = data;
	while (d->max_eat == 0 || d->max_eat > check_with_mutex_b(d, 2))
	{
		if (d->time_to_die <= (get_time_b() - check_with_mutex_2_b(&d->p)))
		{
			msg_dead_b(d);
			return (NULL);
		}
	}
	return (NULL);
}

void	waiting_room_b(int time_to_wait, t_data *data)
{
	struct timeval	now_time;

	if (!check_with_mutex_b(data, 1))
	{
		gettimeofday(&now_time, NULL);
		while ((get_time_b() - ((now_time.tv_sec * 1000)
					+ (now_time.tv_usec / 1000))) < time_to_wait)
			usleep(100);
	}
}

int	check_with_mutex_b(t_data *data, int check)
{
	int	ret;

	ret = 0;
	if (check == 1)
	{
		if (!sem_wait(data->check_dead_c))
		{
			ret = data->check_dead;
			sem_post(data->check_dead_c);
		}
	}
	if (check == 2)
	{
		if (!sem_wait(data->now_times_eat_c))
		{
			ret = data->p.now_times_eat;
			sem_post(data->now_times_eat_c);
		}
	}
	return (ret);
}

long	check_with_mutex_2_b(t_philos *p)
{
	long	ret;

	ret = 0;
	if (!sem_wait(p->now_eat_lock))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&p->now_eat, NULL);
		ret = ((p->now_eat.tv_sec * 1000) + (p->now_eat.tv_usec / 1000));
		sem_post(p->now_eat_lock);
	}
	return (ret);
}
