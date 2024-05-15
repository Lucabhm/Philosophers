/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/15 16:28:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_eat(t_philos *p);

void	*check_for_death(void *philo)
{
	t_philos		*p;
	int				max_eat;
	struct timeval	now_time;
	int				count;

	count = 0;
	p = philo;
	max_eat = p->max_times_eat;
	while (check_eat(p))
	{
		if (max_eat != p->now_times_eat || max_eat == 0)
		{
			if (p->now_eat.tv_sec == 0)
				gettimeofday(&(p)->now_eat, NULL);
			gettimeofday(&now_time, NULL);
			if (p->max_death < calc_time(now_time, p->now_eat))
			{
				gettimeofday(&p->now_death, NULL);
				write_msg(5, calc_time(p->now_death, p->start), p->nbr_philo);
				while (p->nbr_of_philos > count)
				{
					pthread_detach(p->philo);
					p = p->next;
					count++;
				}
				return (NULL);
			}
		}
		p = p->next;
	}
	return (NULL);
}

int	check_eat(t_philos *p)
{
	int	i;

	i = 0;
	while (p->nbr_of_philos > i)
	{
		if (p->max_times_eat != p->now_times_eat || p->max_times_eat == 0)
			return (1);
		p = p->next;
		i++;
	}
	return (0);
}

int	check_death(t_philos *p)
{
	int	i;

	i = 0;
	while (p->nbr_of_philos > i)
	{
		if (p->now_death.tv_sec)
			return (1);
		p = p->next;
		i++;
	}
	return (0);
}
