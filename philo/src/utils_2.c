/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:20:38 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/16 18:07:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error(char *msg, t_philos **philos)
{
	if (philos)
		clean_up(philos);
	ft_putstr_fd(msg, 2);
}

void	clean_up(t_philos **philos)
{
	int			nbr_philos;
	int			i;
	t_philos	*philo;
	t_philos	*next;

	i = 0;
	philo = *philos;
	nbr_philos = philo->data->nbr_of_philos;
	while (nbr_philos > i)
	{
		next = philo->next;
		pthread_mutex_destroy(&(philo)->fork);
		free(philo);
		philo = next;
		i++;
	}
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argc > i)
		{
			j = 0;
			while (argv[i][j])
			{
				if ((int)argv[i][j] < '0' || (int)argv[i][j] > '9')
					return (error(ERROR_3, NULL), 1);
				else if ((int)argv[i][0] == '0')
					return (error(ERROR_3, NULL), 1);
				j++;
			}
			i++;
		}
	}
	else
		return (error(ERROR_0, NULL), 1);
	return (0);
}
