/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/16 18:18:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_eat(t_philos *p);

void	*check_for_death(void *philo)
{
	t_philos		*p;
	int				count;

	count = 0;
	p = philo;
	while ((p->data->max_eat > p->now_times_eat || p->data->max_eat == 0)
		&& !check_death(p))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&(p)->now_eat, NULL);
		if (p->data->time_to_die <= calc_time(p->now_eat))
		{
			usleep(100);
			if (check_death(p) == 0)
			{
				gettimeofday(&p->now_death, NULL);
				write_msg(5, calc_time(p->start), p->nbr_philo, p);
			}
			return (NULL);
		}
	}
	return (NULL);
}

int	check_eat(t_philos *p)
{
	int	i;

	i = 0;
	while (p->data->nbr_of_philos > i)
	{
		if (p->data->max_eat != p->now_times_eat || p->data->max_eat == 0)
			return (1);
		p = p->next;
		i++;
	}
	return (0);
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

void	waiting_room(int time_to_wait)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (calc_time(start) < time_to_wait)
		usleep(time_to_wait / 10);
}
