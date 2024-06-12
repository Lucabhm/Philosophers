/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/12 17:56:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	msg_thinking_b(t_data *data)
{
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf("%ld %i is thinking\n", calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_eating_b(t_data *data)
{
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf("%ld %i is eating\n", calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_sleeping_b(t_data *data)
{
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf("%ld %i is sleeping\n", calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}

void	msg_dead_b(t_data *data)
{
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
	{
		printf("%ld %i died\n", calc_time_b(data), data->p.nbr_philo);
		sem_wait(data->check_dead_c);
		data->check_dead = 1;
		sem_post(data->check_dead_c);
	}
	sem_post(data->write);
}

void	msg_fork_b(t_data *data)
{
	sem_wait(data->write);
	if (!check_with_sem(data, 1))
		printf("%ld %i has taken a fork\n", calc_time_b(data), data->p.nbr_philo);
	sem_post(data->write);
}
