/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:22:17 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 13:22:06 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	parsing_b(int argc, char **argv, t_data *data)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	if (data->nbr_of_philos > 200)
		error_b(ERROR_7, data);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = 0;
	data->start = 0;
	data->ids = NULL;
	data->forks = create_sem("/fork", data->nbr_of_philos, data);
	data->write = create_sem("/write", 1, data);
}

sem_t	*create_sem(char *name, int size, t_data *data)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, size);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_unlink(name);
			sem = sem_open(name, O_CREAT | O_EXCL, 0644, size);
		}
		else
			error_b(ERROR_4, data);
	}
	return (sem);
}

void	check_input_b(int argc, char **argv)
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
				error_b(ERROR_8, NULL);
			while (argv[i][j])
			{
				if ((int)argv[i][j] < '0' || (int)argv[i][j] > '9')
					error_b(ERROR_3, NULL);
				else if ((int)argv[i][0] == '0')
					error_b(ERROR_3, NULL);
				j++;
			}
			i++;
		}
	}
	else
		error_b(ERROR_0, NULL);
}

t_philos	create_philo_b(void)
{
	t_philos	philo;

	philo.nbr_philo = 0;
	philo.now_eat = 0;
	philo.now_times_eat = 0;
	return (philo);
}

void	error_b(char *msg, t_data *data)
{
	if (data)
	{
		sem_close(data->forks);
		sem_close(data->write);
		sem_unlink("/fork");
		sem_unlink("/write");
	}
	ft_putstr_fd(msg, 2);
	exit(1);
}
