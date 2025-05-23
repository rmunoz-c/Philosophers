/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:49:09 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:49:09 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_done(t_philo *philo)
{
	int		retvalue;

	retvalue = 0;
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (philo->meals_eaten >= philo->s_data->max_meals)
		retvalue = 1;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (retvalue);
}

static int	handle_death_check(t_data *data, size_t i, t_philo *philo)
{
	time_t	now;

	pthread_mutex_lock(&data->philos[i].last_meal_mutex);
	now = get_time();
	if (now - philo->last_meal >= philo->s_data->time_to_die)
	{
		pthread_mutex_lock(&data->logs_mutex);
		death_log(&data->philos[i]);
		set_is_alive(&data->philos[i], 0);
		stop_simulation(data, 1);
		pthread_mutex_unlock(&data->logs_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	*reaper(void *arg)
{
	t_data	*data;
	size_t	i;
	size_t	done;

	data = (t_data *)arg;
	while (!get_stop_simulation(data))
	{
		i = 0;
		done = 0;
		while (i < data->n_philos && !get_stop_simulation(data))
		{
			done += philo_done(&data->philos[i]);
			if (handle_death_check(data, i, &data->philos[i]))
				return (NULL);
			i++;
		}
		if (done == data->n_philos)
		{
			stop_simulation(data, 1);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
