/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/13 09:05:35 by lbohm            ###   ########.fr       */
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
	pthread_t	*threads;

	i = 0;
	data->p = create_philo_b(data);
	data->start = get_time_b();
	threads = (pthread_t *)malloc (sizeof(pthread_t) * data->nbr_of_philos);
	if (!threads)
		error_b(ERROR_2, data);
	while (data->nbr_of_philos > i)
	{
		data->p.nbr_philo = i + 1;
		pthread_create(&threads[i], NULL, child, data);
		i++;
	}
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	wait_for_processes(data, data->nbr_of_philos);
}

void	*child(void *data)
{
	t_data		*d;
	static int	i = 0;
	pid_t		pid;

	d = (t_data *)data;
	sem_wait(d->test);
	pid = fork();
	if (pid < 0)
		error_b(ERROR_5, d);
	if (pid == 0)
		dining_room_b(d, i + 1);
	if (pid > 0)
	{
		d->ids[i] = pid;
		i++;
	}
	sem_post(d->test);
	return (NULL);
}

void	dining_room_b(t_data *d, int i)
{
	d->p.nbr_philo = i;
	d->p.now_eat = d->start;
	pthread_create(&d->p.check, NULL, check_for_death_b, d);
	if (d->p.nbr_philo % 2 != 0)
		waiting_room_b(d->time_to_eat / 2, d);
	while (d->max_eat == 0 || d->max_eat > check_with_sem(d, 2))
	{
		if (check_with_sem(d, 1))
			break ;
		msg_thinking_b(d);
		take_forks_and_eat_b(d);
		msg_sleeping_b(d);
		waiting_room_b(d->time_to_sleep, d);
		sem_wait(d->now_times_eat_c);
		d->p.now_times_eat++;
		sem_post(d->now_times_eat_c);
	}
	pthread_join(d->p.check, NULL);
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

void	wait_for_processes(t_data *data, int nbr_of_philos)
{
	int	i;
	int	status;

	i = 0;
	while (nbr_of_philos > i)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
			kill_processes(data);
		i++;
	}
}
