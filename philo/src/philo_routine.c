/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 18:31:50 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-30 18:31:50 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		return ;
	}
	usleep_control(philo->s_data->time_to_sleep);
	sleep_log(philo);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
}

void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive)
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		return ;
	}
	think_log(philo);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
}

void	start_philo_routine(t_philo *philo)
{
	eat_routine(philo);
	sleep_routine(philo);
	think_routine(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
	{
		usleep_control(40);
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
	while (1)
	{
		take_forks(philo, philo->first_fork, philo->second_fork);
		start_philo_routine(philo);
	}
	return (NULL);
}
