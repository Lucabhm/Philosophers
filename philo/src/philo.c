/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/11 13:50:29 by lbohm            ###   ########.fr       */
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
	data->start = get_time();
	while (data->nbr_of_philos > i)
	{
		first->now_eat = data->start;
		pthread_create(&first->philo, NULL, dining_room, first);
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
	msg_thinking(p);
	if (p->data->nbr_of_philos == 1)
		return (NULL);
	if (p->nbr_philo % 2 != 0)
		waiting_room(p->data->time_to_eat / 2, p);
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex(p, 2))
	{
		if (check_with_mutex(p, 1))
			break ;
		if (p->nbr_philo % 2 == 0)
			take_forks_and_eat(p, &p->next->fork, &p->fork);
		else
		{
			usleep(100);
			take_forks_and_eat(p, &p->fork, &p->next->fork);
		}
	}
	return (NULL);
}

void	take_forks_and_eat(t_philos *p,
	pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	msg_fork(p);
	pthread_mutex_lock(fork2);
	msg_fork(p);
	msg_eating(p);
	waiting_room(p->data->time_to_eat, p);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
	usleep(500);
	pthread_mutex_lock(&p->now_eat_lock);
	p->now_eat = get_time();
	pthread_mutex_unlock(&p->now_eat_lock);
	msg_sleeping(p);
	waiting_room(p->data->time_to_sleep, p);
	pthread_mutex_lock(&p->now_times_eat_c);
	p->now_times_eat++;
	pthread_mutex_unlock(&p->now_times_eat_c);
	msg_thinking(p);
}
