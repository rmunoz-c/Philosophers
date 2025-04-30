/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 17:50:08 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-30 17:50:08 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->logs_mutex, NULL) != 0)
	{
		write(2, "❌ Error initializing logs mutex\n", 33);
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		write(2, "❌ Error initializing death mutex\n", 34);
		return (0);
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		write(2, "❌ Error initializing stop mutex\n", 33);
		return (0);
	}
	if (pthread_mutex_init(&data->philos_done_mutex, NULL) != 0)
	{
		write(2, "❌ Error initializing philo done mutex\n", 39);
		return (0);
	}
	return (1);
}

int	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = (pthread_mutex_t *) malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "❌ Error initializing forks mutex\n", 34);
			return (0);
		}
		i++;
	}
	return (1);
}
