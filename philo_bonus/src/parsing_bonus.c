/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:22:17 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/06 13:55:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	parsing_b(int argc, char **argv, t_data *data)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = 0;
	data->start.tv_sec = 0;
	data->start.tv_usec = 0;
	data->check_dead = 0;
	data->ids = (int *)malloc (data->nbr_of_philos * (sizeof(int)));
	if (!data->ids)
		error(ERROR_2, data);
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nbr_of_philos);
	if (data->forks == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(data->forks);
			sem_unlink("/forks");
			data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nbr_of_philos);
		}
		else
			error(ERROR_4, data);
	}
	data->write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1);
	if (data->write == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(data->write);
			sem_unlink("/write");
			data->write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1);
		}
		else
			error(ERROR_4, data);
	}
	data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 1);
	if (data->death == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(data->death);
			sem_unlink("/death");
			data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 1);
		}
		else
			error(ERROR_4, data);
	}
	data->check_dead_c = sem_open("/check_dead", O_CREAT | O_EXCL, 0644, 1);
	if (data->check_dead_c == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(data->check_dead_c);
			sem_unlink("/check_dead");
			data->check_dead_c = sem_open("/check_dead", O_CREAT | O_EXCL, 0644, 1);
		}
		else
			error(ERROR_4, data);
	}
	data->now_times_eat_c = sem_open("/now_times", O_CREAT | O_EXCL, 0644, 1);
	if (data->now_times_eat_c == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(data->now_times_eat_c);
			sem_unlink("/now_times");
			data->now_times_eat_c = sem_open("/now_times", O_CREAT | O_EXCL, 0644, 1);
		}
		else
			error(ERROR_4, data);
	}
	return (0);
}

int	check_input_b(int argc, char **argv)
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

void	create_philo_b(t_philos *p, t_data *data, int i)
{
	p->nbr_philo = i;
	p->now_eat.tv_sec = 0;
	p->now_eat.tv_usec = 0;
	p->now_death.tv_sec = 0;
	p->now_death.tv_usec = 0;
	p->now_times_eat = 0;
	p->data = data;
	p->now_eat_lock = sem_open("/now_eat", O_CREAT | O_EXCL, 0644, 0);
	if (p->now_eat_lock == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_close(p->now_eat_lock);
			sem_unlink("/now_eat");
			p->now_eat_lock = sem_open("/now_eat", O_CREAT | O_EXCL, 0644, data->nbr_of_philos);
		}
		else
			error(ERROR_4, data);
	}
}

void	error(char *msg, t_data *data)
{
	if (data)
	{
		sem_close(data->forks);
		sem_close(data->write);
		sem_close(data->death);
		sem_unlink("/forks");
		sem_unlink("/write");
		sem_unlink("/death");
	}
	ft_putstr_fd(msg, 2);
	exit(1);
}
