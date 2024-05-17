/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/17 16:35:17 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.philos = NULL;
	if (check_input_b(argc, argv) || parsing_b(argc, argv, &data))
		return (1);
	start_processes(&data);
	clean_up_b(&data);
	exit(0);
}

void	start_processes(t_data *data)
{
	int	i;
	int	ids[data->nbr_of_philos];

	i = 0;
	while (data->nbr_of_philos > i)
	{
		ids[i] = fork_philos(data);
		i++;
	}
	i = 0;
	while (data->nbr_of_philos > i)
	{
		waitpid(ids[i], NULL, 0);
		i++;
	}
}

int	fork_philos(t_data *data)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		error_b(ERROR_4, NULL);
	if (id == 0)
		init_data_for_philo(data);
	return (id);
}

void	init_data_for_philo(t_data *data)
{
	pthread_t	check;

	
}

void	dining_room_b(t_data *data)
{
	
}
