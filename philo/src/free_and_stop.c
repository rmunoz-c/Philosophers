/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:39:31 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/05/12 20:57:36 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

void	free_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i++]);
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->logs_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->philos_done_mutex);
	free(data->threads);
	free(data->forks);
	free(data->philos);
}

int	get_stop_simulation(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->stop_mutex);
	val = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (val);
}

void	stop_simulation(t_data *data, int val)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_simulation = val;
	pthread_mutex_unlock(&data->stop_mutex);
}
