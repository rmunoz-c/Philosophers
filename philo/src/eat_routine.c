/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 16:01:41 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-09 16:01:41 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	write(1, "HOLA\n", 5);
	pthread_mutex_lock(first);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive || philo->s_data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		pthread_mutex_unlock(first);
		return (0);
	}
	fork_log(philo, 1);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive || philo->s_data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (0);
	}
	fork_log(philo, 1);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	return (1);
}

static void	drop_forks_and_log(t_philo *philo,
								pthread_mutex_t *first,
								pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	fork_log(philo, 0);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	pthread_mutex_unlock(first);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	fork_log(philo, 0);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
}


void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	eat_log(philo);
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	philo->last_meal = get_time();
	if (philo->meals_eaten > -1
		&& philo->meals_eaten < philo->s_data->max_meals)
		philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	usleep_control(philo->s_data->time_to_eat);
	drop_forks_and_log(philo, philo->first_fork, philo->second_fork);
}
