/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/17 10:58:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;

	data.philos = NULL;
	if (check_input(argc, argv) || parsing(argc, argv, &data)
		|| create_philos(&data))
		return (1);
	start_threads(&data);
	clean_up(&data.philos);
	return (0);
}

int	start_threads(t_data *data)
{
	int				i;
	t_philos		*first;

	i = 0;
	first = data->philos;
	while (data->nbr_of_philos > i)
	{
		pthread_create(&(first)->philo, NULL, dining_room, first);
		pthread_create(&(first)->check, NULL, check_for_death, first);
		first = first->next;
		i++;
	}
	first = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(first->philo, NULL);
		pthread_join(first->check, NULL);
		first = first->next;
		i++;
	}
	return (0);
}

void	*dining_room(void *philo)
{
	t_philos	*p;

	p = philo;
	gettimeofday(&(p)->start, NULL);
	gettimeofday(&(p)->now_eat, NULL);
	if (p->nbr_philo % 2 == 0)
		usleep(100);
	while ((p->data->max_eat > p->now_times_eat || p->data->max_eat == 0)
		&& !check_death(p))
	{
		write_msg(1, calc_time(p->start), p->nbr_philo, p);
		if (p->data->nbr_of_philos == 1)
			break ;
		take_forks_and_eat(p);
		write_msg(4, calc_time(p->start), p->nbr_philo, p);
		waiting_room(p->data->time_to_sleep);
		p->now_times_eat++;
	}
	return (NULL);
}

void	take_forks_and_eat(t_philos *p)
{
	if (!pthread_mutex_lock(&(p)->fork))
	{
		if (!pthread_mutex_lock(&(p)->next->fork))
		{
			write_msg(2, calc_time(p->start), p->nbr_philo, p);
			waiting_room(p->data->time_to_eat);
			gettimeofday(&(p)->now_eat, NULL);
			pthread_mutex_unlock(&(p)->next->fork);
		}
		pthread_mutex_unlock(&(p)->fork);
	}
}
