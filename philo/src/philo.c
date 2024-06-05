/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/05 19:06:52 by lbohm            ###   ########.fr       */
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
	pthread_t		check;

	i = 0;
	first = data->philos;
	gettimeofday(&data->start, NULL);
	while (data->nbr_of_philos > i)
	{
		pthread_create(&(first)->philo, NULL, dining_room, first);
		first = first->next;
		i++;
	}
	pthread_create(&check, NULL, check_for_death, first);
	first = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(first->philo, NULL);
		first = first->next;
		i++;
	}
	pthread_join(check, NULL);
	return (0);
}

void	*dining_room(void *philo)
{
	t_philos	*p;

	p = philo;
	if (!pthread_mutex_lock(&p->now_eat_lock))
	{
		gettimeofday(&(p)->now_eat, NULL);
		pthread_mutex_unlock(&p->now_eat_lock);
	}
	msg_thinking(p);
	if (p->nbr_philo % 2 != 0)
		waiting_room(p->data->time_to_eat / 2, p);
	if (p->data->nbr_of_philos == 1)
		return (NULL);
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex(p, 2))
	{
		if (check_with_mutex(p, 1))
			break ;
		if (p->nbr_philo == p->data->nbr_of_philos)
			take_forks_and_eat(p, &p->next->fork, &p->fork);
		else
			take_forks_and_eat(p, &p->fork, &p->next->fork);
	}
	return (NULL);
}

void	take_forks_and_eat(t_philos *p,
	pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(&p->data->take);
	if (!pthread_mutex_lock(fork1))
	{
		msg_fork(p);
		if (!pthread_mutex_lock(fork2))
		{
			pthread_mutex_unlock(&p->data->take);
			msg_fork(p);
			msg_eating(p);
			waiting_room(p->data->time_to_eat, p);
			if (!pthread_mutex_lock(&p->now_eat_lock))
			{
				gettimeofday(&(p)->now_eat, NULL);
				pthread_mutex_unlock(&p->now_eat_lock);
			}
			pthread_mutex_unlock(fork2);
		}
		pthread_mutex_unlock(fork1);
	}
	msg_sleeping(p);
	waiting_room(p->data->time_to_sleep, p);
	if (!pthread_mutex_lock(&p->data->now_times_eat_c))
	{
		p->now_times_eat++;
		pthread_mutex_unlock(&p->data->now_times_eat_c);
	}
	msg_thinking(p);
}
