/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 12:50:56 by lbohm            ###   ########.fr       */
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
	int			i;
	pid_t		pid;
	int			ids[201];

	i = 0;
	data->p = create_philo_b();
	data->start = get_time_b();
	while (data->nbr_of_philos > i)
	{
		pid = fork();
		if (pid < 0)
			error_b(ERROR_5, data);
		if (pid == 0)
			dining_room_b(data, i + 1);
		if (pid > 0)
		{
			ids[i] = pid;
			i++;
		}
	}
	wait_for_processes(data, ids);
}

void	dining_room_b(t_data *d, int i)
{
	d->p.nbr_philo = i;
	d->p.now_eat = d->start;
	if (d->nbr_of_philos == 1)
		waiting_room_b(d->time_to_die + 1, d);
	if (d->p.nbr_philo % 2 != 0)
		waiting_room_b(d->time_to_eat / 2, d);
	while ((d->max_eat == 0 || d->max_eat > d->p.now_times_eat))
	{
		msg_thinking_b(d);
		take_forks_and_eat_b(d);
		msg_sleeping_b(d);
		waiting_room_b(d->time_to_sleep, d);
		d->p.now_times_eat++;
	}
	clean_up_child(d);
	exit(0);
}

void	take_forks_and_eat_b(t_data *data)
{
	sem_wait(data->forks);
	msg_fork_b(data);
	sem_wait(data->forks);
	msg_fork_b(data);
	msg_eating_b(data);
	waiting_room_b(data->time_to_eat, data);
	sem_post(data->forks);
	sem_post(data->forks);
	data->p.now_eat = get_time_b();
}

void	wait_for_processes(t_data *data, int *ids)
{
	int	i;
	int	status;

	i = 0;
	while (data->nbr_of_philos > i)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
			kill_processes(data, ids);
		i++;
	}
}
