/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:43:45 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/06 14:12:54 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*check_for_death_b(void *philo)
{
	t_philos	*p;

	p = philo;
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex_b(p, 2))
	{
		if (p->data->time_to_die <= (get_time_b() - check_with_mutex_2_b(p)))
		{
			msg_dead_b(p);
			fprintf(stderr, "dead\n");
			return (NULL);
		}
	}
	return (NULL);
}

void	waiting_room_b(int time_to_wait, t_philos *p)
{
	struct timeval	now_time;

	if (!check_with_mutex_b(p, 1))
	{
		gettimeofday(&now_time, NULL);
		while ((get_time_b() - ((now_time.tv_sec * 1000)
					+ (now_time.tv_usec / 1000))) < time_to_wait)
			usleep(100);
	}
}

int	check_with_mutex_b(t_philos *p, int check)
{
	int	ret;

	ret = 0;
	if (check == 1)
	{
		if (!sem_wait(p->data->check_dead_c))
		{
			ret = p->data->check_dead;
			sem_post(p->data->check_dead_c);
		}
	}
	if (check == 2)
	{
		if (!sem_wait(p->data->now_times_eat_c))
		{
			ret = p->now_times_eat;
			sem_post(p->data->now_times_eat_c);
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
