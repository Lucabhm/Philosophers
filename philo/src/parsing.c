/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:22:17 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 13:29:53 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parsing(int argc, char **argv, t_data *data)
{
	int	tmp_nbr_of_philos;
	int	tmp_time_to_die;
	int	tmp_time_to_eat;
	int	tmp_time_to_sleep;
	int	tmp_max_eat;

	tmp_nbr_of_philos = ft_atoi(argv[1]);
	tmp_time_to_die = ft_atoi(argv[2]);
	tmp_time_to_eat = ft_atoi(argv[3]);
	tmp_time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		tmp_max_eat = ft_atoi(argv[5]);
	else
		tmp_max_eat = 0;
	data->nbr_of_philos = tmp_nbr_of_philos;
	data->time_to_die = tmp_time_to_die;
	data->time_to_eat = tmp_time_to_eat;
	data->time_to_sleep = tmp_time_to_sleep;
	data->max_eat = tmp_max_eat;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->check_dead_c, NULL);
	data->check_dead = 0;
	data->start = 0;
	return (0);
}

int	create_philos(t_data *data)
{
	int				i;
	t_philos		*philo;

	i = 0;
	philo = (t_philos *)malloc (sizeof(t_philos) * data->nbr_of_philos);
	if (!philo)
		return (error(ERROR_2, NULL), 1);
	while (data->nbr_of_philos > i)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		pthread_mutex_init(&philo[i].now_eat_lock, NULL);
		pthread_mutex_init(&philo[i].now_times_eat_c, NULL);
		philo[i].nbr_philo = i + 1;
		philo[i].now_eat = 0;
		philo[i].now_times_eat = 0;
		philo[i].data = data;
		philo[i].next = NULL;
		ft_lstadd_back(&data->philos, &philo[i]);
		i++;
	}
	i--;
	return (philo[i].next = data->philos, 0);
}

int	check_input(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argc > i)
		{
			j = 0;
			if (check_max_min_b(argv[i]))
				return (error(ERROR_5, data), 1);
			while (argv[i][j])
			{
				if ((int)argv[i][j] < '0' || (int)argv[i][j] > '9')
					return (error(ERROR_3, data), 1);
				else if ((int)argv[i][0] == '0')
					return (error(ERROR_3, data), 1);
				j++;
			}
			i++;
		}
	}
	else
		return (error(ERROR_0, data), 1);
	return (0);
}

void	clean_up(t_data *data)
{
	int			nbr_philos;
	int			i;
	t_philos	*philo;
	t_philos	*next;

	i = 0;
	if (data->philos)
	{
		philo = data->philos;
		nbr_philos = philo->data->nbr_of_philos;
		pthread_mutex_destroy(&philo->data->write);
		pthread_mutex_destroy(&philo->data->check_dead_c);
		while (nbr_philos > i)
		{
			next = philo->next;
			pthread_mutex_destroy(&philo->fork);
			pthread_mutex_destroy(&philo->now_eat_lock);
			pthread_mutex_destroy(&philo->now_times_eat_c);
			philo = next;
			i++;
		}
		free(data->philos);
	}
	if (data)
		free(data);
}

int	check_max_min_b(char *str)
{
	int	nbr;
	int	strnbr;

	nbr = ft_strlen(str);
	strnbr = ft_atoi(str);
	if ((nbr == 11 && str[0] == '-' && strnbr > 0)
		|| (nbr > 11 && str[0] == '-')
		|| (nbr == 10 && str[0] != '-' && strnbr < 0)
		|| (nbr > 10 && str[0] != '-'))
		return (1);
	return (0);
}
