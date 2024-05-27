/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:31 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/27 15:37:30 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// struct

typedef struct s_data
{
	struct s_philos	*philos;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
}				t_data;

typedef struct s_philos
{
	pthread_t			philo;
	pthread_t			check;
	pthread_mutex_t		fork;
	struct timeval		start;
	struct timeval		now_death;
	struct timeval		now_eat;
	int					now_times_eat;
	int					nbr_philo;
	struct s_data		*data;
	struct s_philos		*next;
}				t_philos;

// monitoring

void	*check_for_death(void *philo);
int		check_death(t_philos *p);
void	waiting_room(int time_to_wait, t_philos *p);

// parsing

int		check_input(int argc, char **argv);
int		parsing(int argc, char **argv, t_data *data);
int		create_philos(t_data *data);
void	error(char *msg, t_philos **philos);
void	clean_up(t_philos **philos);

// philo

int		main(int argc, char **argv);
int		start_threads(t_data *data);
void	*dining_room(void *philo);
void	take_forks_and_eat(t_philos *p);

// utils

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *ascii);
void	ft_lstadd_back(t_philos **lst, t_philos *new);
long	calc_time(struct timeval start);
void	write_msg(int msg, long time, int nbr, t_philos *p);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"

#endif