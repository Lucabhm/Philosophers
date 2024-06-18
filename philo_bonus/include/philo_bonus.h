/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:29:09 by lbohm             #+#    #+#             */
/*   Updated: 2024/06/18 10:27:34 by lbohm            ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>

// struct

typedef struct s_philos
{
	long				now_eat;
	int					now_times_eat;
	int					nbr_philo;
}				t_philos;

typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				*ids;
	long			start;
	sem_t			*forks;
	sem_t			*write;
	struct s_philos	p;
}				t_data;

// utils_bonus_2

void		waiting_room_b(int time_to_wait, t_data *data);
void		clean_up_child(t_data *data);
void		clean_up_b(t_data *data);
void		kill_processes(t_data *data, int *ids);
size_t		ft_strlen(const char *str);

// parsing_bonus

void		parsing_b(int argc, char **argv, t_data *data);
sem_t		*create_sem(char *name, int size, t_data *data);
void		check_input_b(int argc, char **argv);
t_philos	create_philo_b(void);
void		error_b(char *msg, t_data *data);

// philo_bonus

int			main(int argc, char **argv);
void		start_processes(t_data *data);
void		dining_room_b(t_data *data, int i);
void		take_forks_and_eat_b(t_data *data);
void		wait_for_processes(t_data *data, int *ids);

// utils_bonus

void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *ascii);
long		get_time_b(void);
long		calc_time_b(t_data *data);
int			check_max_min_b(char *str);

// msgs_bonus

void		msg_thinking_b(t_data *data);
void		msg_eating_b(t_data *data);
void		msg_sleeping_b(t_data *data);
void		msg_dead_b(t_data *data);
void		msg_fork_b(t_data *data);

// error msg

# define ERROR_0 "Invalid nbr of arrguments\n"
# define ERROR_1 "Too many philos than possible\n"
# define ERROR_2 "Allocation failed\n"
# define ERROR_3 "Invalid argument\n"
# define ERROR_4 "sem_open failed\n"
# define ERROR_5 "fork failed\n"
# define ERROR_6 "sem failed\n"
# define ERROR_7 "Too many philos\n"
# define ERROR_8 "Value is bigger or smaller than an int\n"

#endif