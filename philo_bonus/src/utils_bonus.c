/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:18:41 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/17 13:12:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

long	get_time_b(void)
{
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	return (((now_time.tv_sec * 1000) + (now_time.tv_usec / 1000)));
}

long	calc_time_b(t_data *data)
{
	struct timeval	now_time;
	long			now;

	gettimeofday(&now_time, NULL);
	now = now_time.tv_sec * 1000 + now_time.tv_usec / 1000;
	return (now - data->start);
}

int	check_max_min_b(char *str)
{
	int	nbr;
	int	strnbr;

	nbr = ft_strlen(str);
	strnbr = ft_atoi(str);
	if ((nbr == 11 && str[0] == '-' && strnbr > 0)
		|| (nbr > 11 && str[0] == '-')
		|| (nbr == 10 && str[0] != '-' && strnbr < 0)
		|| (nbr > 10 && str[0] != '-'))
		return (1);
	return (0);
}
