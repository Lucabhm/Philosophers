/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/27 15:37:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_for_death(void *philo)
{
	t_philos		*p;

	p = philo;
	while ((p->data->max_eat > p->now_times_eat || p->data->max_eat == 0)
		&& !check_death(p))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&(p)->now_eat, NULL);
		if (p->data->time_to_die <= calc_time(p->now_eat))
		{
			usleep(100);
			if (!pthread_mutex_lock(&p->data->dead) && check_death(p) == 0)
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

int	check_death(t_philos *p)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p->data->nbr_of_philos > i)
	{
		if (p->now_death.tv_sec)
			count++;
		p = p->next;
		i++;
	}
	return (count);
}

void	waiting_room(int time_to_wait, t_philos *p)
{
	struct timeval	start;

	if (!check_death(p))
	{
		gettimeofday(&start, NULL);
		while (calc_time(start) < time_to_wait)
			usleep(time_to_wait / 10);
	}
}
