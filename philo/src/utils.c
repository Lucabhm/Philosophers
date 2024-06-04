/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:56:16 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/04 15:55:37 by lbohm            ###   ########.fr       */
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

long	calc_time(struct timeval start, t_philos *p)
{
	long			start_time;
	long			now;
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	// if (p->now_eat_test2 == 1)
	// {
	// 	p->now_eat_test1.tv_sec = now_time.tv_sec + (p->data->max_eat / 1000);
	// 	p->now_eat_test1.tv_usec = now_time.tv_usec;
	// }
	now = (now_time.tv_sec * 1000) + (now_time.tv_usec / 1000);
	start_time = start.tv_sec * 1000 + (start.tv_usec / 1000);
	return (now - start_time);
}

long	get_time(void)
{
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	return (((now_time.tv_sec * 1000) + (now_time.tv_usec / 1000)));
}

void	write_msg(int msg, int nbr, t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		if (!check_with_mutex(p, 1))
		{
			time = get_time() - ((p->data->start.tv_sec * 1000) + (p->data->start.tv_usec / 1000));
			// msgs(msg, time, nbr, p);
			if (msg == 1)
				printf("%ld %i \e[0;33mis thinking\e[0m\n", time, nbr);
			else if (msg == 2)
				printf("%ld %i has taken a fork\n", time, nbr);
			else if (msg == 3)
				printf("%ld %i \e[0;32mis eating\e[0m\n", time, nbr);
			else if (msg == 4)
				printf("%ld %i \e[0;34mis sleeping\e[0m\n", time, nbr);
			else if (msg == 5)
			{
				printf("\033[0;31m%ld ms %i died\033[0m\n", time, nbr);
				if (!pthread_mutex_lock(&p->data->check_dead_c))
				{
					p->data->check_dead = 1;
					pthread_mutex_unlock(&p->data->check_dead_c);
				}
			}
		}
		pthread_mutex_unlock(&p->data->write);
	}
}
