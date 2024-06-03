/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:56:16 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/03 12:23:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *ascii)
{
	int	result;
	int	negative;
	int	i;

	i = 0;
	negative = 1;
	result = 0;
	while (ascii[i] == ' ' || (ascii[i] > 8 && ascii[i] < 14))
		i++;
	if (ascii[i] == '-' || ascii[i] == '+')
	{
		if (ascii[i] == '-')
			negative *= -1;
		i++;
	}
	while (ascii[i] > 47 && ascii[i] < 58)
	{
		result = (ascii[i] - '0') + (result * 10);
		i++;
	}
	return (result * negative);
}

void	ft_lstadd_back(t_philos **lst, t_philos *new)
{
	t_philos	*now;

	if (!(*lst))
	{
		*lst = new;
	}
	else
	{
		now = *lst;
		while (now->next)
			now = now->next;
		now->next = new;
	}
}

long	calc_time(struct timeval start)
{
	long			start_time;
	long			now;
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	now = (now_time.tv_sec * 1000) + (now_time.tv_usec / 1000);
	start_time = start.tv_sec * 1000 + (start.tv_usec / 1000);
	return (now - start_time);
}

// void	write_msg(int msg, int nbr, t_philos *p)
// {
// 	long	time;

// 	time = 0;
// 	if (!pthread_mutex_lock(&p->data->write))
// 	{
// 		if (!check_with_mutex(p, 1))
// 		{
// 			time = calc_time(p->data->start);
// 			// msgs(msg, time, nbr, p);
// 		}
// 		pthread_mutex_unlock(&p->data->write);
// 	}
// }
