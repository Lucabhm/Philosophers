/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/07 12:09:17 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_input_b(argc, argv);
	parsing_b(argc, argv, &data);
	start_processes(&data);
	clean_up_b(&data);
	return (0);
}

void	start_processes(t_data *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	data->p = create_philo_b(data);
	gettimeofday(&data->start, NULL);
	while (data->nbr_of_philos > i)
	{
		pid = fork();
		if (pid < 0)
			error(ERROR_5, data);
		if (pid != 0)
			data->ids[i] = pid;
		i++;
	}
	if (pid == 0)
		dining_room_b(data, i + 1);
	wait_for_processes(data, data->nbr_of_philos);
}

void	dining_room_b(t_data *d, int i)
{
	d->p.nbr_philo = i;
	pthread_create(&d->p.check, NULL, check_for_death_b, d);
	if (!sem_wait(d->p.now_eat_lock))
	{
		if (d->p.now_eat.tv_sec == 0)
			gettimeofday(&d->p.now_eat, NULL);
		sem_post(d->p.now_eat_lock);
	}
	msg_thinking_b(d);
	if (d->p.nbr_philo % 2 != 0)
		waiting_room_b(d->time_to_eat / 2, d);
	while (d->max_eat == 0 || d->max_eat > check_with_mutex_b(d, 2))
	{
		if (check_with_mutex_b(d, 1))
			break ;
		take_forks_and_eat_b(d);
		msg_sleeping_b(d);
		waiting_room_b(d->time_to_sleep, d);
		msg_thinking_b(d);
		usleep(500);
		d->p.now_times_eat++;
	}
	pthread_join(d->p.check, NULL);
	exit(d->check_dead);
}

void	take_forks_and_eat_b(t_data *data)
{
	if (sem_wait(data->forks) == -1)
		error(ERROR_6, data);
	else
	{
		msg_fork_b(data);
		if (sem_wait(data->forks) == -1)
		{
			sem_post(data->forks);
			error(ERROR_6, data);
		}
		else
		{
			msg_fork_b(data);
			msg_eating_b(data);
			waiting_room_b(data->time_to_eat, data);
			if (!sem_wait(data->p.now_eat_lock))
			{
				gettimeofday(&data->p.now_eat, NULL);
				sem_post(data->p.now_eat_lock);
			}
			sem_post(data->forks);
			sem_post(data->forks);
		}
	}
}

void	wait_for_processes(t_data *data, int nbr_of_philos)
{
	int	i;
	int	status;

	i = 0;
	while (nbr_of_philos > i)
	{
		waitpid(data->ids[i], &status, 0);
		if (WIFEXITED(status))
		{
			kill_processes(data);
			exit(WIFEXITED(status));
		}
		i++;
	}
}
