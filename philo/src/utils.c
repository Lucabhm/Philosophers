/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:56:16 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/15 13:29:17 by lbohm            ###   ########.fr       */
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

long	calc_time(struct timeval first, struct timeval second)
{
	long	first_time;
	long	second_time;

	first_time = (first.tv_sec * 1000) + (first.tv_usec / 1000);
	second_time = second.tv_sec * 1000 + (second.tv_usec / 1000);
	return (first_time - second_time);
}

void	write_msg(int msg, long time, int nbr)
{
	if (msg == 1)
		printf("%ld ms %i \e[0;33mis thinking\e[0m\n", time, nbr);
	else if (msg == 2)
	{
		printf("%ld ms %i has taken a fork\n", time, nbr);
		printf("%ld ms %i has taken a fork\n", time, nbr);
	}
	else if (msg == 3)
		printf("%ld ms %i \e[0;32mis eating\e[0m\n", time, nbr);
	else if (msg == 4)
		printf("%ld ms %i \e[0;34mis sleeping\e[0m\n", time, nbr);
	else if (msg == 5)
		printf("\033[0;31m%ld ms %i is dead\033[0m\n", time, nbr);
}