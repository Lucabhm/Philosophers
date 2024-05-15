/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/15 15:58:43 by lbohm            ###   ########.fr       */
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
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		data->nbr_of_philos = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->times_to_eat = ft_atoi(argv[5]);
		else
			data->times_to_eat = 0;
	}
	else
		return (error(ERROR_0, NULL), 1);
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
		philo->nbr_of_philos = data->nbr_of_philos;
		philo->max_death = data->time_to_die;
		philo->max_eat = data->time_to_eat * 1000;
		philo->max_sleep = data->time_to_sleep * 1000;
		philo->max_times_eat = data->times_to_eat;
		philo->now_eat.tv_sec = 0;
		philo->now_eat.tv_usec = 0;
		// philo->now_time.tv_sec = 0;
		// philo->now_time.tv_usec = 0;
		philo->now_death.tv_sec = 0;
		philo->now_death.tv_usec = 0;
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
	pthread_t		check;

	i = 0;
	first = data->philos;
	while (data->nbr_of_philos > i)
	{
		pthread_create(&(first)->philo, NULL, dining_room, first);
		first = first->next;
		i++;
	}
	pthread_create(&check, NULL, check_for_death, data->philos);
	pthread_join(check, NULL);
	first = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(first->philo, NULL);
		first = first->next;
		i++;
	}
	return (0);
}

void	*dining_room(void *philo)
{
	t_philos	*p;

	p = philo;
	if (p->nbr_philo % 2 == 0)
		usleep(100);
	gettimeofday(&(p)->start, NULL);
	while ((p->max_times_eat > p->now_times_eat || p->max_times_eat == 0)
		&& !check_death(p))
	{
		if (p->nbr_of_philos > 1 && !check_death(p))
		{
			gettimeofday(&(p)->now_think, NULL);
			write_msg(1, calc_time(p->now_think, p->start), p->nbr_philo);
			if (!pthread_mutex_lock(&(p)->fork) && !pthread_mutex_lock(&(p)->next->fork))
			{
				gettimeofday(&(p)->now_eat, NULL);
				write_msg(2, calc_time(p->now_eat, p->start), p->nbr_philo);
				write_msg(3, calc_time(p->now_eat, p->start), p->nbr_philo);
				usleep(p->max_eat);
				gettimeofday(&(p)->now_eat, NULL);
			}
			pthread_mutex_unlock(&(p)->next->fork);
			pthread_mutex_unlock(&(p)->fork);
			gettimeofday(&(p)->now_sleep, NULL);
			write_msg(4, calc_time(p->now_sleep, p->start), p->nbr_philo);
			usleep(p->max_sleep);
		}
		if (p->max_times_eat != 0)
			p->now_times_eat++;
	}
	return (NULL);
}
