/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:41:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/04 15:59:19 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_for_death(void *philo)
{
	t_philos		*p;

	p = philo;
	while (p->data->max_eat == 0 || p->data->max_eat > check_with_mutex(p, 2))
	{
		if (check_with_mutex(p, 1))
			break ;
		if (p->data->time_to_die <= (get_time() - check_with_mutex_2(p)))
		{
			write_msg(5, p->nbr_philo, p);
			return (NULL);
		}
		p = p->next;
	}
	return (NULL);
}

void	waiting_room(int time_to_wait, t_philos *p)
{
	struct timeval	now_time;

	if (!check_with_mutex(p, 1))
	{
		gettimeofday(&now_time, NULL);
		while ((get_time() - ((now_time.tv_sec * 1000) + (now_time.tv_usec / 1000))) < time_to_wait)
			usleep(100);
	}
}

int	check_with_mutex(t_philos *p, int check)
{
	int	ret;

	ret = 0;
	if (check == 1)
	{
		if (!pthread_mutex_lock(&p->data->check_dead_c))
		{
			ret = p->data->check_dead;
			pthread_mutex_unlock(&p->data->check_dead_c);
		}
	}
	if (check == 2)
	{
		if (!pthread_mutex_lock(&p->data->now_times_eat_c))
		{
			ret = p->now_times_eat;
			pthread_mutex_unlock(&p->data->now_times_eat_c);
		}
	}
	return (ret);
}

long	check_with_mutex_2(t_philos *p)
{
	long	ret;

	ret = 0;
	if (!pthread_mutex_lock(&p->now_eat_test))
	{
		if (p->now_eat.tv_sec == 0)
			gettimeofday(&p->now_eat, NULL);
		ret = ((p->now_eat.tv_sec * 1000) + (p->now_eat.tv_usec / 1000));
		pthread_mutex_unlock(&p->now_eat_test);
	}
	return (ret);
}

long	check_with_mutex_3(t_philos *p)
{
	long	ret;

	ret = 0;
	if (!pthread_mutex_lock(&p->data->time))
	{
		if (p->data->jetzt.tv_sec == 0)
			gettimeofday(&p->data->jetzt, NULL);
		ret = ((p->data->jetzt.tv_sec * 1000) + (p->data->jetzt.tv_usec / 1000));
		pthread_mutex_unlock(&p->data->time);
	}
	return (ret);
}

void	msgs(int msg, long time, int nbr, t_philos *p)
{
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

void	msg_thinking(t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		time = get_time() - ((p->data->start.tv_sec * 1000) + (p->data->start.tv_usec / 1000));
		if (!check_with_mutex(p, 1))
			printf("%ld %i is thinking\n", time, p->nbr_philo);
		pthread_mutex_unlock(&p->data->write);
	}
}

void	msg_sleeping(t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		time = get_time() - ((p->data->start.tv_sec * 1000) + (p->data->start.tv_usec / 1000));
		if (!check_with_mutex(p, 1))
			printf("%ld %i is sleeping\n", time, p->nbr_philo);
		pthread_mutex_unlock(&p->data->write);
	}
}

void	msg_fork(t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		time = get_time() - ((p->data->start.tv_sec * 1000) + (p->data->start.tv_usec / 1000));
		if (!check_with_mutex(p, 1))
			printf("%ld %i has taken a fork\n", time, p->nbr_philo);
		pthread_mutex_unlock(&p->data->write);
	}
}

void	msg_eating(t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		time = get_time() - ((p->data->start.tv_sec * 1000) + (p->data->start.tv_usec / 1000));
		p->now_eat_test2 = 1;
		if (!check_with_mutex(p, 1))
			printf("%ld %i is eating\n", time, p->nbr_philo);
		p->now_eat_test2 = 0;
		pthread_mutex_unlock(&p->data->write);
	}
}

// void	msg_test(t_philos *p)
// {
// 	if (!pthread_mutex_lock(&p->data->write))
// 	{
// 		if (!check_with_mutex(p, 1))
// 			printf("%ld %i test\n", calc_time(p->data->start, p), p->nbr_philo);
// 		pthread_mutex_unlock(&p->data->write);
// 	}
// }

void	msg_dead(t_philos *p)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&p->data->write))
	{
		if (!check_with_mutex(p, 1))
		{
			printf("%ld %i died\n", calc_time(p->data->start, p), p->nbr_philo);
			if (!pthread_mutex_lock(&p->data->check_dead_c))
			{
				p->data->check_dead = 1;
				pthread_mutex_unlock(&p->data->check_dead_c);
			}
		}
		pthread_mutex_unlock(&p->data->write);
	}
}

void	*get_time_test(void *data)
{
	t_data	*d;

	d = data;
	while (d->max_eat == 0 || d->max_eat > check_with_mutex(d->philos, 2))
	{
		if (check_with_mutex(d->philos, 1))
			break ;
		if (!pthread_mutex_lock(&d->time))
		{
			gettimeofday(&d->jetzt, NULL);
			pthread_mutex_unlock(&d->time);
		}
		d->philos = d->philos->next;
	}
	return (NULL);
}
