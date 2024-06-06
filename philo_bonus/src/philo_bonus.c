/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/06 14:19:28 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input_b(argc, argv) || parsing_b(argc, argv, &data))
		return (1);
	start_processes(&data);
	clean_up_b(&data);
	return (0);
}

void	start_processes(t_data *data)
{
	pid_t		pid;
	int			i;

	i = 0;
	gettimeofday(&data->start, NULL);
	while (data->nbr_of_philos > i)
	{
		pid = fork();
		if (pid < 0)
			error(ERROR_5, data);
		if (pid == 0)
			dining_room_b(data, i + 1);
		data->ids[i] = pid;
		i++;
	}
	wait_for_processes(data, data->nbr_of_philos);
}

void	dining_room_b(t_data *data, int i)
{
	t_philos	p;

	create_philo_b(&p, data, i);
	pthread_create(&p.check, NULL, check_for_death_b, &p);
	if (!sem_wait(p.now_eat_lock))
	{
		if (p.now_eat.tv_sec == 0)
			gettimeofday(&p.now_eat, NULL);
		sem_post(p.now_eat_lock);
	}
	msg_thinking_b(&p);
	if (p.nbr_philo % 2 != 0)
		waiting_room_b(p.data->time_to_eat / 2, &p);
	while (p.data->max_eat == 0 || p.data->max_eat > check_with_mutex_b(&p, 2))
	{
		if (check_with_mutex_b(&p, 1))
			break ;
		take_forks_and_eat_b(data, &p);
		msg_sleeping_b(&p);
		waiting_room_b(data->time_to_sleep, &p);
		msg_thinking_b(&p);
		usleep(500);
		p.now_times_eat++;
	}
	pthread_join(p.check, NULL);
	exit(p.data->check_dead);
}

void	take_forks_and_eat_b(t_data *data, t_philos *p)
{
	if (sem_wait(data->forks) == -1)
		error(ERROR_6, data);
	else
	{
		msg_fork_b(p);
		if (sem_wait(data->forks) == -1)
		{
			sem_post(data->forks);
			error(ERROR_6, data);
		}
		else
		{
			msg_fork_b(p);
			msg_eating_b(p);
			waiting_room_b(data->time_to_eat, p);
			if (!sem_wait(p->now_eat_lock))
			{
				gettimeofday(&p->now_eat, NULL);
				sem_post(p->now_eat_lock);
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
