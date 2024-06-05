/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:22:17 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/05 18:56:29 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->check_dead_c, NULL);
	pthread_mutex_init(&data->now_times_eat_c, NULL);
	pthread_mutex_init(&data->take, NULL);
	data->check_dead = 0;
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
		pthread_mutex_init(&(philo)->now_eat_lock, NULL);
		philo->nbr_philo = i + 1;
		philo->now_eat.tv_sec = 0;
		philo->now_eat.tv_usec = 0;
		philo->now_times_eat = 0;
		philo->data = data;
		philo->next = NULL;
		ft_lstadd_back(&data->philos, philo);
		i++;
	}
	return (philo->next = data->philos, 0);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argc > i)
		{
			j = 0;
			while (argv[i][j])
			{
				if ((int)argv[i][j] < '0' || (int)argv[i][j] > '9')
					return (error(ERROR_3, NULL), 1);
				else if ((int)argv[i][0] == '0')
					return (error(ERROR_3, NULL), 1);
				j++;
			}
			i++;
		}
	}
	else
		return (error(ERROR_0, NULL), 1);
	return (0);
}

void	error(char *msg, t_philos **philos)
{
	if (philos)
		clean_up(philos);
	ft_putstr_fd(msg, 2);
}

void	clean_up(t_philos **philos)
{
	int			nbr_philos;
	int			i;
	t_philos	*philo;
	t_philos	*next;

	i = 0;
	philo = *philos;
	nbr_philos = philo->data->nbr_of_philos;
	pthread_mutex_destroy(&philo->data->dead);
	pthread_mutex_destroy(&philo->data->write);
	pthread_mutex_destroy(&philo->data->check_dead_c);
	pthread_mutex_destroy(&philo->data->now_times_eat_c);
	while (nbr_philos > i)
	{
		next = philo->next;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->now_eat_lock);
		free(philo);
		philo = next;
		i++;
	}
}
