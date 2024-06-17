/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 09:19:45 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	msg_thinking_b(t_data *data)
{
	const char	*format;

	format = "%ld %i is thinking\n";
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf(format, calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_eating_b(t_data *data)
{
	const char	*format;

	format = "%ld %i is eating\n";
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf(format, calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_sleeping_b(t_data *data)
{
	const char	*format;

	format = "%ld %i is sleeping\n";
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf(format, calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_dead_b(t_data *data)
{
	const char	*format;

	format = "%ld %i died\n";
	sem_wait(data->write);
	printf(format, calc_time_b(data), data->p.nbr_philo);
	pthread_detach(data->checker[data->p.nbr_philo - 1]);
	clean_up_child(data);
	exit(1);
}

void	msg_fork_b(t_data *data)
{
	const char	*format;

	format = "%ld %i has taken a fork\n";
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf(format, calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}
