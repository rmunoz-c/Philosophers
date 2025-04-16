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


typedef struct s_data
{
	pthread_mutex_t	*forks;  // Array de mutexes, uno por cada tenedor (entre filósofos vecinos)
	pthread_mutex_t	logs_mutex; // Mutex para sincronizar mensajes por pantalla (evita que se mezclen prints)
	pthread_mutex_t	death_mutex; // Protege la condición de muerte para evitar condiciones de carrera
	pthread_mutex_t	stop_mutex; // Protege la variable stop_simulation de accesos simultáneos
	pthread_mutex_t	philos_done_mutex; // Protege el contador de filósofos que terminaron (philos_done)
	
	pthread_t		*threads; // Array de hilos (uno por cada filósofo) si se usa de forma centralizada
	uint64_t		init_time; // Marca de tiempo cuando empieza la simulación (referencia base)
	uint64_t		time_to_die; // Tiempo máximo sin comer antes de morir
	uint64_t		time_to_eat; // Tiempo que tarda en comer
	uint64_t		time_to_sleep; // Tiempo que tarda en dormir

	unsigned int	n_philos; // Número total de filósofos
	unsigned int	philos_done; // Número de filósofos que alcanzaron max_meals (si aplica)
	unsigned int	max_meals; // Número máximo de comidas por filósofo (si es parte del objetivo)

	int				stop_simulation; // Flag para indicar si la simulación debe terminar
}					t_data;

typedef struct s_philo
{
	t_data			*s_data; // Puntero a la estructura compartida (para acceso global)
	pthread_mutex_t	last_meal_mutex; // Protege el campo last_meal de accesos simultáneos
	pthread_mutex_t	*left_fork; // Puntero al mutex del tenedor a su izquierda
	pthread_mutex_t	*right_fork; // Puntero al mutex del tenedor a su derecha

	uint64_t		last_meal; // Tiempo de la última comida del filósofo
	unsigned int	meals_eaten; // Cantidad de veces que ha comido
	unsigned int	id;	// ID único del filósofo (de 1 a n_philos)

	pthread_t		thread; // Hilo individual del filósofo
}				t_philo;



#endif