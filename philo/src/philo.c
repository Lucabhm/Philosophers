/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/13 12:10:34 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc (sizeof(t_data));
	if (!data)
		return (error(ERROR_2, NULL), 1);
	data->philos = NULL;
	if (check_input(argc, argv) || parsing(argc, argv, data)
		|| create_philos(data))
		return (1);
	start_threads(data);
	clean_up(&data->philos);
	return (0);
}

int	start_threads(t_data *data)
{
	t_philos		*first;
	pthread_t		check;

	first = data->philos;
	data->start = get_time();
	if (pthread_create(&check, NULL, check_for_death, first))
		return (error(ERROR_4, &data->philos), 1);
	while (first)
	{
		if (pthread_create(&first->philo, NULL, dining_room, first))
			return (error(ERROR_4, &data->philos), 1);
		first = first->next;
		if (first == data->philos)
			break ;
	}
	first = data->philos;
	while (first)
	{
		if (pthread_join(first->philo, NULL))
			return (error(ERROR_4, &data->philos), 1);
		first = first->next;
		if (first == data->philos)
			break ;
	}
	if (pthread_join(check, NULL))
		return (error(ERROR_4, &data->philos), 1);
	return (0);
}

void	*dining_room(void *philo)
{
	t_philos	*p;

	p = philo;
	if (p->data->nbr_of_philos == 1)
		return (NULL);
	if (p->nbr_philo % 2 != 0)
		waiting_room(p->data->time_to_eat / 2, p);
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex(p, 2))
	{
		if (check_with_mutex(p, 1))
			break ;
		if (p->nbr_philo % 2 == 0)
			take_forks_and_eat(p, &p->fork, &p->next->fork);
		else
			take_forks_and_eat(p, &p->next->fork, &p->fork);
	}
	return (NULL);
}

void	take_forks_and_eat(t_philos *p,
	pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	msg_thinking(p);
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
	p->now_times_eat++;
	pthread_mutex_unlock(&p->now_eat_lock);
	msg_sleeping(p);
	waiting_room(p->data->time_to_sleep, p);
}
