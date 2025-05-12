/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:16:59 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/05/12 20:56:24 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

static int	philo_has_died(t_philo *philo)
{
	time_t	now;
	time_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	now = get_time();
	return ((now - last_meal) >= philo->s_data->time_to_die);
}

static int	all_philos_done(t_data *data)
{
	size_t	done;

	pthread_mutex_lock(&data->philos_done_mutex);
	done = data->philos_done;
	pthread_mutex_unlock(&data->philos_done_mutex);
	return (done == data->n_philos);
}

static int	handle_death_check(t_data *data, size_t i)
{
	if (philo_has_died(&data->philos[i]))
	{
		pthread_mutex_lock(&data->logs_mutex);
		stop_simulation(data, 1);
		death_log(&data->philos[i]);
		pthread_mutex_unlock(&data->logs_mutex);
		return (1);
	}
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
		while (i < data->n_philos)
		{
			if (philo_has_died(&data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
