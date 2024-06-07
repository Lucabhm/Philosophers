/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:56:16 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/07 16:04:14 by lbohm            ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	return (now_time.tv_sec * 1000 + now_time.tv_usec / 1000);
}
