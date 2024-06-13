/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:31 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/13 11:53:50 by lbohm            ###   ########.fr       */
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
	pthread_mutex_t	write;
	pthread_mutex_t	check_dead_c;
	long			start;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				check_dead;
}				t_data;

typedef struct s_philos
{
	struct s_philos		*next;
	struct s_data		*data;
	pthread_t			philo;
	pthread_mutex_t		fork;
	pthread_mutex_t		now_eat_lock;
	long				now_eat;
	int					now_times_eat;
	int					nbr_philo;
}				t_philos;

// monitoring

void			*check_for_death(void *philo);
void			waiting_room(int time_to_wait, t_philos *p);
int				check_with_mutex(t_philos *p, int check);
long			check_with_mutex_2(t_philos *p);

// parsing

int				check_input(int argc, char **argv);
int				parsing(int argc, char **argv, t_data *data);
int				create_philos(t_data *data);
void			error(char *msg, t_philos **philos);
void			clean_up(t_philos **philos);

// philo

int				main(int argc, char **argv);
int				start_threads(t_data *data);
void			*dining_room(void *philo);
void			take_forks_and_eat(t_philos *p,
					pthread_mutex_t *fork1, pthread_mutex_t *fork2);

// utils

void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *ascii);
void			ft_lstadd_back(t_philos **lst, t_philos *new);
long			get_time(void);
long			calc_time(t_philos *p);

// msgs

void			msg_thinking(t_philos *p);
void			msg_sleeping(t_philos *p);
void			msg_fork(t_philos *p);
void			msg_eating(t_philos *p);
void			msg_dead(t_philos *p);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"
# define ERROR_4 "Thread creation failed\n"

#endif