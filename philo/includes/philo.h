/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 14:26:41 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-15 14:26:41 by rmunoz-c         ###   ########.fr       */
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

struct s_data;


typedef struct s_philo
{
	struct s_data			*s_data; // Puntero a la estructura compartida (para acceso global)
	// pthread_mutex_t	last_meal_mutex; // Protege el campo last_meal de accesos simultáneos
	pthread_mutex_t	*left_fork; // Puntero al mutex del tenedor a su izquierda
	pthread_mutex_t	*right_fork; // Puntero al mutex del tenedor a su derecha
	pthread_mutex_t	*first_fork; // Puntero al mutex del primer tenedor
	pthread_mutex_t	*second_fork; // Puntero al mutex del segundo tenedor
	uint64_t		last_meal; // Tiempo de la última comida del filósofo
	uint64_t		born_time; // Marca de tiempo en que el filósofo se crea y empieza la rutina
	unsigned int	is_alive; // Indica si el filosofo sigue vivo (1 si está vivo, 0 si no lo está)
	int	meals_eaten; // Cantidad de veces que ha comido
	unsigned int	id;	// ID único del filósofo (de 1 a n_philos)
	pthread_t		thread; // Hilo individual del filósofo
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks; // Array de mutexes, uno por cada tenedor (entre filósofos vecinos)
	pthread_mutex_t	logs_mutex; // Mutex para sincronizar mensajes por pantalla (evita que se mezclen prints)
	pthread_mutex_t	death_mutex; // Protege la condición de muerte para evitar condiciones de carrera
	pthread_mutex_t	stop_mutex; // Protege la variable stop_simulation de accesos simultáneos
	pthread_mutex_t	philos_done_mutex; // Protege el contador de filósofos que terminaron (philos_done)
	pthread_t		*threads; // Array de hilos (uno por cada filósofo) si se usa de forma centralizada
	uint64_t		init_time; // Marca de tiempo cuando empieza la simulación (referencia base)
	uint64_t		time_to_die; // Tiempo máximo sin comer antes de morir
	uint64_t		time_to_eat; // Tiempo que tarda en comer
	uint64_t		time_to_sleep; // Tiempo que tarda en dormir
	t_philo			*philos;
	unsigned int	n_philos; // Número total de filósofos
	unsigned int	philos_done; // Número de filósofos que alcanzaron max_meals (si aplica)
	int				max_meals; // Número máximo de comidas por filósofo (si es parte del objetivo)
	int				stop_simulation; // Flag para indicar si la simulación debe terminar
}					t_data;


# define MAX_PHILOS 200

/*eat_routine.c*/
int			take_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second);
void		eat_routine(t_philo *philo);

/*free.c*/
void	free_all(t_data *data);

/*init.c*/
int			init_mutex(t_data *data);
int			alloc_data(t_data *data);
int			init_forks(t_data *data);
int			init(int argc, char **argv, t_data *data);

/*logs.c*/
void		fork_log(t_philo *philo, size_t equip);
void		eat_log(t_philo *philo);
void		sleep_log(t_philo *philo);
void		think_log(t_philo *philo);
void		death_log(t_philo *philo);

/*parser.c*/
int			create_args(int argc, char **argv, size_t *val);
int			check_args(int argc, char **argv, t_data *data);

/*philo_routine.c*/
void		*philo_routine(void *arg);

/*usleep.c*/
uint64_t	get_time(void);
void		usleep_control(__useconds_t miliseconds);

#endif