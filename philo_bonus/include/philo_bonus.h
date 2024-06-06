/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:29:09 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/06 15:06:49 by lbohm            ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>

// struct

typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				*ids;
	int				check_dead;
	struct timeval	start;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*death;
	sem_t			*check_dead_c;
	sem_t			*now_times_eat_c;
}				t_data;

typedef struct s_philos
{
	pthread_t			check;
	struct timeval		now_death;
	struct timeval		now_eat;
	int					now_times_eat;
	int					nbr_philo;
	int					pid;
	t_data				*data;
	sem_t				*now_eat_lock;
}				t_philos;

// monitoring_bonus

void	*check_for_death_b(void *philo);
void	waiting_room_b(int time_to_wait, t_philos *p);
int		check_with_mutex_b(t_philos *p, int check);
long	check_with_mutex_2_b(t_philos *p);

// parsing_bonus

int		check_input_b(int argc, char **argv);
int		parsing_b(int argc, char **argv, t_data *data);
void	create_philo_b(t_philos *p, t_data *data, int i);
void	error(char *msg, t_data *data);

// philo_bonus

int		main(int argc, char **argv);
void	start_processes(t_data *data);
void	dining_room_b(t_data *data, int i);
void	take_forks_and_eat_b(t_data *data, t_philos *p);
void	wait_for_processes(t_data *data, int nbr_of_philos);

// utils_bonus

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *ascii);
long	get_time_b(void);
void	clean_up_b(t_data *data);
void	kill_processes(t_data *data);

// msgs_bonus

void	msg_thinking_b(t_philos *p);
void	msg_eating_b(t_philos *p);
void	msg_sleeping_b(t_philos *p);
void	msg_dead_b(t_philos *p);
void	msg_fork_b(t_philos *p);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"
# define ERROR_4 "sem_open failed\n"
# define ERROR_5 "fork failed\n"
# define ERROR_6 "sem failed\n"

#endif