/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:31 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/04 14:48:39 by lbohm            ###   ########.fr       */
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
	int				lastphilo;
	struct timeval	jetzt;
	pthread_mutex_t	time;
	struct timeval	start;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	pthread_mutex_t	check_dead_c;
	pthread_mutex_t	now_times_eat_c;
	int				check_dead;
}				t_data;

typedef struct s_philos
{
	pthread_t			philo;
	pthread_mutex_t		fork;
	pthread_mutex_t		now_eat_test;
	struct timeval		now_eat;
	struct timeval		now_time;
	struct timeval		now_time2;
	int					now_eat_test2;
	struct timeval		now_eat_test1;
	int					now_times_eat;
	int					nbr_philo;
	struct s_data		*data;
	struct s_philos		*next;
}				t_philos;

// monitoring

void			*check_for_death(void *philo);
void			waiting_room(int time_to_wait, t_philos *p);
int				check_with_mutex(t_philos *p, int check);
long			check_with_mutex_2(t_philos *p);
long			check_with_mutex_3(t_philos *p);
void			msgs(int msg, long time, int nbr, t_philos *p);
void			msg_thinking(t_philos *p);
void			msg_sleeping(t_philos *p);
void			msg_fork(t_philos *p);
void			msg_eating(t_philos *p);
void			msg_test(t_philos *p);
void			msg_dead(t_philos *p);
void			*get_time_test(void *data);

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
void			take_forks_and_eat(t_philos *p);

// utils

void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *ascii);
void			ft_lstadd_back(t_philos **lst, t_philos *new);
long			calc_time(struct timeval start, t_philos *p);
long			get_time(void);
void			write_msg(int msg, int nbr, t_philos *p);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"

#endif