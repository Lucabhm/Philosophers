/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:18:41 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/14 13:54:28 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *ascii)
{
	int	result;
	int	negative;
	int	i;

	i = 0;
	negative = 1;
	result = 0;
	while (ascii[i] == ' ' || (ascii[i] > 8 && ascii[i] < 14))
		i++;
	if (ascii[i] == '-' || ascii[i] == '+')
	{
		if (ascii[i] == '-')
			negative *= -1;
		i++;
	}
	while (ascii[i] > 47 && ascii[i] < 58)
	{
		result = (ascii[i] - '0') + (result * 10);
		i++;
	}
	return (result * negative);
}

long	get_time_b(void)
{
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	return (((now_time.tv_sec * 1000) + (now_time.tv_usec / 1000)));
}

long	calc_time_b(t_data *data)
{
	struct timeval	now_time;
	long			now;

	gettimeofday(&now_time, NULL);
	now = now_time.tv_sec * 1000 + now_time.tv_usec / 1000;
	return (now - data->start);
}

void	clean_up_b(t_data *data)
{
	sem_close(data->p.now_eat_lock);
	sem_close(data->p.now_times_eat_c);
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->check_dead_c);
	sem_unlink("/now_times");
	sem_unlink("/now_eat");
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/check_death");
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
