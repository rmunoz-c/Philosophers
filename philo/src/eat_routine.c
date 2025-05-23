/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:48:44 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:48:44 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	take_first_fork(t_philo *philo, pthread_mutex_t *first)
{
	pthread_mutex_lock(first);
	if (!get_is_alive(philo) || get_stop_simulation(philo->s_data))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (get_is_alive(philo))
		fork_log(philo, 1);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	return (1);
}

int	take_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (!take_first_fork(philo, first))
		return (0);
	if (philo->s_data->n_philos == 1)
	{
		usleep_control(philo->s_data->time_to_die + 1, philo);
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->is_alive_mutex);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(&philo->is_alive_mutex);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_unlock(&philo->is_alive_mutex);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	fork_log(philo, 1);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	return (1);
}

void	drop_forks_and_log(t_philo *philo, pthread_mutex_t *first,
			pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
}

void	eat_routine(t_philo *philo)
{
	if (!get_is_alive(philo))
	{
		return ;
	}
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	eat_log(philo);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep_control(philo->s_data->time_to_eat, philo);
}
