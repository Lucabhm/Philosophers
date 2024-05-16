/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/16 18:06:33 by lbohm            ###   ########.fr       */
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

int	parsing(int argc, char **argv, t_data *data)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = 0;
	return (0);
}

int	create_philos(t_data *data)
{
	int				i;
	t_philos		*philo;

	i = 0;
	while (data->nbr_of_philos > i)
	{
		philo = (t_philos *)malloc (sizeof(*philo));
		if (!philo)
			return (error(ERROR_2, &philo), 1);
		pthread_mutex_init(&(philo)->fork, NULL);
		philo->nbr_philo = i + 1;
		philo->now_eat.tv_sec = 0;
		philo->now_eat.tv_usec = 0;
		philo->now_death.tv_sec = 0;
		philo->now_death.tv_usec = 0;
		philo->start.tv_sec = 0;
		philo->start.tv_usec = 0;
		philo->now_times_eat = 0;
		philo->data = data;
		philo->next = NULL;
		ft_lstadd_back(&data->philos, philo);
		i++;
	}
	return (philo->next = data->philos, 0);
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
		if (!pthread_mutex_lock(&(p)->fork) && !pthread_mutex_lock(&(p)->next->fork))
		{
			write_msg(2, calc_time(p->start), p->nbr_philo, p);
			write_msg(3, calc_time(p->start), p->nbr_philo, p);
			waiting_room(p->data->time_to_eat);
			gettimeofday(&(p)->now_eat, NULL);
		}
		pthread_mutex_unlock(&(p)->next->fork);
		pthread_mutex_unlock(&(p)->fork);
		write_msg(4, calc_time(p->start), p->nbr_philo, p);
		waiting_room(p->data->time_to_sleep);
		if (p->data->max_eat != 0)
			p->now_times_eat++;
	}
	return (NULL);
}
