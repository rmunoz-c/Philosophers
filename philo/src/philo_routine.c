/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:48:08 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:48:08 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleep_routine(t_philo *philo)
{
	if (!philo->is_alive || get_stop_simulation(philo->s_data))
		return ;
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	sleep_log(philo);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
	usleep_control(philo->s_data->time_to_sleep, philo);
}

void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->logs_mutex);
	if (!philo->is_alive || get_stop_simulation(philo->s_data))
	{
		pthread_mutex_unlock(&philo->s_data->logs_mutex);
		return ;
	}
	think_log(philo);
	pthread_mutex_unlock(&philo->s_data->logs_mutex);
}

void	start_philo_routine(t_philo *philo)
{
	if (get_stop_simulation(philo->s_data))
	{
		drop_forks_and_log(philo, philo->first_fork, philo->second_fork);
		return ;
	}
	eat_routine(philo);
	drop_forks_and_log(philo, philo->first_fork, philo->second_fork);
	if (get_stop_simulation(philo->s_data))
		return ;
	sleep_routine(philo);
	if (get_stop_simulation(philo->s_data))
		return ;
	think_routine(philo);
}

static void	set_forks_order(t_philo *philo)
{
	if (philo->id % 2)
	{
		usleep_control(50, philo);
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_forks_order(philo);
	while (1)
	{
		if (get_stop_simulation(philo->s_data)
			|| !get_is_alive(philo))
			break ;
		if (philo->id % 2)
			usleep_control(1, philo);
		if (take_forks(philo, philo->first_fork, philo->second_fork))
			start_philo_routine(philo);
	}
	return (NULL);
}
