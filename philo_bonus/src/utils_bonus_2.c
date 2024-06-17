/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:43:45 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 13:23:09 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	waiting_room_b(int time_to_wait, t_data *data)
{
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	if (data->time_to_die > time_to_wait + (get_time_b() - data->p.now_eat))
	{
		while ((get_time_b() - ((now_time.tv_sec * 1000)
					+ (now_time.tv_usec / 1000))) < time_to_wait)
			usleep(100);
	}
	else
	{
		while (get_time_b() - data->p.now_eat < data->time_to_die)
			usleep(100);
		msg_dead_b(data);
	}
}

void	clean_up_child(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write);
}

void	clean_up_b(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write);
	sem_unlink("/fork");
	sem_unlink("/write");
}

void	kill_processes(t_data *data, int *ids)
{
	int	i;

	i = 0;
	while (data->nbr_of_philos > i)
	{
		kill(ids[i], SIGKILL);
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
