/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:49:26 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:49:26 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include "utils.h"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*s_data;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	is_alive_mutex;
	uint64_t		last_meal;
	unsigned int	is_alive;
	int				meals_eaten;
	unsigned int	id;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	philos_done_mutex;
	pthread_t		*threads;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		born_time;
	t_philo			*philos;
	unsigned int	n_philos;
	unsigned int	philos_done;
	int				max_meals;
	int				stop_simulation;
}					t_data;

# define MAX_PHILOS 200

/*eat_routine.c*/
int			take_forks(t_philo *philo, pthread_mutex_t *first,
				pthread_mutex_t *second);
void		drop_forks_and_log(t_philo *philo, pthread_mutex_t *first,
				pthread_mutex_t *second);
void		eat_routine(t_philo *philo);

/*free.c*/
void		free_all(t_data *data);
int			get_is_alive(t_philo *philo);
void		set_is_alive(t_philo *philo, int val);
int			get_stop_simulation(t_data *data);
void		stop_simulation(t_data *data, int val);

/*init.c*/
int			init_mutex(t_data *data);
int			alloc_data(t_data *data);
int			init_forks(t_data *data);
void		init_philos(t_data *data);
int			init(int argc, char **argv, t_data *data);

/*logs.c*/
void		fork_log(t_philo *philo, size_t equip);
void		eat_log(t_philo *philo);
void		sleep_log(t_philo *philo);
void		think_log(t_philo *philo);
void		death_log(t_philo *philo);

/*main.c*/
int			main(int argc, char **argv);

/*parser.c*/
int			create_args(int argc, char **argv, size_t *val);
int			check_args(int argc, char **argv, t_data *data);

/*philo_routine.c*/
void		sleep_routine(t_philo *philo);
void		think_routine(t_philo *philo);
void		start_philo_routine(t_philo *philo);
void		*philo_routine(void *arg);

/*reaper.c*/
void		*reaper(void *arg);

/*usleep.c*/
uint64_t	get_time(void);
void		usleep_control(__useconds_t time_in_ms, t_philo *philo);

#endif