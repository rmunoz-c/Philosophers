/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 16:00:12 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 16:00:12 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include "utils.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	struct s_data	*s_data;
	pid_t			pid;
	sem_t			*meal_lock;
	uint64_t		last_meal;
	int				meals_eaten;
	unsigned int	id;

}				t_philo;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*log_lock;
	sem_t			*stop_lock;
	sem_t			*philos_full;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		born_time;
	t_philo			*philos;
	unsigned int	n_philos;
	int				max_meals;
	int				stop_simulation;
}				t_data;

# define MAX_PHILOS 200

/*eat_routine.c*/
// void		cleanup_forks_semaphores(t_data *data, unsigned int count);
// int			init_forks_semaphores(t_data *data);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eat_routine(t_philo *philo);

/*free.c*/
void		kill_all_philos(t_data *data);
void		cleanup(t_data *data);
int			get_stop_simulation(t_data *data);

/*init.c*/
int			alloc_data(t_data *data);
int			init_semaphores(t_data *data);
void		init_philos(t_data *data);
int			init(int argc, char **argv, t_data *data);

/*logs.c*/
void		log_action(t_philo *philo, const char *msg);

/*main.c*/
int			main(int argc, char **argv);

/*parser.c*/
int			create_args(int argc, char **argv, size_t *val);
int			check_args(int argc, char **argv, t_data *data);

/*philo_routine.c*/
void		philo_routine(t_philo *philo);

/*reaper.c*/
void		set_stop_simulation(t_data *data, int value);
void		reaper(t_data *data);
void		*monitor_death(void *arg);

/*usleep.c*/
uint64_t	get_time(void);
void		usleep_control(__useconds_t time_in_ms, t_philo *philo);

#endif