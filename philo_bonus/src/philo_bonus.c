/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/14 13:47:49 by lbohm            ###   ########.fr       */
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
	data->p = create_philo_b(data);
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
	pthread_create(&d->p.check, NULL, check_for_death_b, d);
	if (d->nbr_of_philos == 1)
		waiting_room_b(d->time_to_die + 1, d);
	if (d->p.nbr_philo % 2 != 0)
		waiting_room_b(d->time_to_eat / 2, d);
	while ((d->max_eat == 0 || d->max_eat > check_with_sem(d, 2))
		&& !check_with_sem(d, 1))
	{
		msg_thinking_b(d);
		take_forks_and_eat_b(d);
		msg_sleeping_b(d);
		waiting_room_b(d->time_to_sleep, d);
		sem_wait(d->p.now_times_eat_c);
		d->p.now_times_eat++;
		sem_post(d->p.now_times_eat_c);
	}
	pthread_detach(d->p.check);
	clean_up_b(d);
	exit(d->check_dead);
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
	sem_wait(data->p.now_eat_lock);
	data->p.now_eat = get_time_b();
	sem_post(data->p.now_eat_lock);
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
