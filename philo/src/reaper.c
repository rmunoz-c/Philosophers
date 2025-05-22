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

static int	all_philos_done(t_data *data)
{
	size_t	done;

	pthread_mutex_lock(&data->philos_done_mutex);
	done = data->philos_done;
	pthread_mutex_unlock(&data->philos_done_mutex);
	return (done == data->n_philos);
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
		pthread_mutex_unlock(&data->logs_mutex);
		set_is_alive(&data->philos[i], 0);
		stop_simulation(data, 1);
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

	data = (t_data *)arg;
	while (!get_stop_simulation(data))
	{
		if (all_philos_done(data))
		{
			stop_simulation(data, 1);
			return (NULL);
		}
		i = 0;
		while (i < data->n_philos && !get_stop_simulation(data))
		{
			if (handle_death_check(data, i, &data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
