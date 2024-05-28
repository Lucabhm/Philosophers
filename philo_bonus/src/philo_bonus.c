/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/28 14:05:33 by lbohm            ###   ########.fr       */
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
	while (data->nbr_of_philos > i)
	{
		pid = fork();
		if (pid < 0)
			error(ERROR_5, data);
		if (pid == 0)
			dining_room_b(data, i + 1);
		data->id[i] = pid;
		i++;
	}
	wait_for_processes(data, data->nbr_of_philos);
}

void	dining_room_b(t_data *data, int i)
{
	t_philos	p;

	create_philo_b(&p, data, i);
	pthread_create(&p.check, NULL, check_for_death_b, &p);
	gettimeofday(&p.start, NULL);
	gettimeofday(&p.now_eat, NULL);
	if (p.nbr_philo % 2 == 0)
		usleep(100);
	while (data->max_eat > p.now_times_eat || data->max_eat == 0)
	{
		write_msg_b(1, calc_time_b(p.start), p.nbr_philo, &p);
		if (sem_wait(data->forks) == -1)
			error(ERROR_6, data);
		else
		{
			if (sem_wait(data->forks) == -1)
			{
				sem_post(data->forks);
				error(ERROR_6, data);
			}
			else
			{
				write_msg_b(2, calc_time_b(p.start), p.nbr_philo, &p);
				waiting_room_b(data->time_to_eat);
				gettimeofday(&p.now_eat, NULL);
				sem_post(data->forks);
				sem_post(data->forks);
			}
		}
		write_msg_b(4, calc_time_b(p.start), p.nbr_philo, &p);
		waiting_room_b(data->time_to_sleep);
		p.now_times_eat++;
	}
	pthread_join(p.check, NULL);
	exit(0);
}

void	wait_for_processes(t_data *data, int nbr_of_philos)
{
	int	i;
	int	status;

	i = 0;
	while (nbr_of_philos > i)
	{
		waitpid(data->id[i], NULL, 0);
		if (WIFEXITED(status))
			exit(WIFEXITED(status));
		i++;
	}
}
