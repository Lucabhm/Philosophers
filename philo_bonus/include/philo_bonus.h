/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:29:09 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/27 14:57:17 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
#include <signal.h>

// struct

typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				*id;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*death;
}				t_data;

typedef struct s_philos
{
	pthread_t			check;
	struct timeval		start;
	struct timeval		now_death;
	struct timeval		now_eat;
	int					now_times_eat;
	int					nbr_philo;
	int					pid;
	t_data				*data;
}				t_philos;

// monitoring_bonus

void	*check_for_death_b(void *philo);
void	waiting_room_b(int time_to_wait);
void	start_processes(t_data *data);
void	wait_for_processes(int *nbr, int nbr_of_philos);
void	dining_room_b(t_data *data, int i);
void	kill_processes(t_philos *p);

// parsing_bonus

int		check_input_b(int argc, char **argv);
int		parsing_b(int argc, char **argv, t_data *data);
void	create_philo_b(t_philos *p, t_data *data, int i);
void	error(char *msg, t_data *data);

// philo_bonus

int		main(int argc, char **argv);
int		start_threads(t_data *data);
void	*dining_room(void *philo);
void	take_forks_and_eat(t_philos *p);

// utils_bonus

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *ascii);
long	calc_time_b(struct timeval start);
void	write_msg_b(int msg, long time, int nbr, t_philos *p);
void	clean_up_b(t_data *data);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"
# define ERROR_4 "sem_open failed\n"
# define ERROR_5 "fork failed\n"
# define ERROR_6 "sem failed\n"

#endif