/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:20:38 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/15 14:17:19 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	*check_for_death(void *philo)
// {
// 	t_philos	*p;
// 	int			i;
// 	int			count;

// 	p = philo;
// 	i = 0;
// 	count = 0;
// 	while (p->max_times_eat >= i)
// 	{
// 		if (p->now_eat.tv_sec == 0)
// 			gettimeofday(&(p)->now_eat, NULL);
// 		gettimeofday(&(p)->now_time, NULL);
// 		if (p->max_death < calc_time(p->now_time, p->now_eat) && p->max_times_eat != p->now_times_eat)
// 		{
// 			gettimeofday(&(p)->now_death, NULL);
// 			write_msg(5, calc_time(p->now_death, p->start), p->nbr_philo);
// 			while (p->nbr_of_philos > count)
// 			{
// 				pthread_detach(p->philo);
// 				p = p->next;
// 				count++;
// 			}
// 			return (NULL);
// 		}
// 		if (p->max_times_eat <= p->now_times_eat && p->max_times_eat != 0)
// 			i++;
// 		else
// 			i = 0;
// 		p = p->next;
// 	}
// 	return (NULL);
// }

void	error(char *msg, t_philos **philos)
{
	if (philos)
		freelist(philos);
	ft_putstr_fd(msg, 2);
}

void	freelist(t_philos **philos)
{
	int			nbr_philos;
	int			i;
	t_philos	*philo;
	t_philos	*next;

	i = 0;
	philo = *philos;
	nbr_philos = philo->nbr_of_philos;
	while (nbr_philos > i)
	{
		next = philo->next;
		pthread_mutex_destroy(&(philo)->fork);
		free(philo);
		philo = next;
	}
}

int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (1);
	else
		return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argc > i)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error(ERROR_3, NULL), 1);
			j++;
		}
		i++;
	}
	return (0);
}
