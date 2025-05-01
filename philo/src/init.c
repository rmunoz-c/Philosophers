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

int	alloc_data(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->threads)
	{
		write(2, "❌ Error: could not allocate threads\n", 37);
		return (0);
	}
	data->forks = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		write(2, "❌ Error: could not allocate forks\n", 35);
		free(data->threads);
		return (0);
	}
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
	{
		write(2, "❌ Error: could not allocate philos\n", 36);
		free(data->threads);
		free(data->forks);
		return (0);
	}
	return (1);
}

int	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "❌ Error initializing forks mutex\n", 34);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].right_fork = &data->forks[data->n_philos - 1];
		else
			data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (1);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].s_data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
		{
			write(2, "❌ Error initializing philo's last_meal_mutex\n", 49);
			while (i > 0)
				pthread_mutex_destroy(&data->philos[--i].last_meal_mutex);
			return ;
		}
		i++;
	}
}

int	init(int argc, char **argv, t_data *data)
{
	if (!check_args(argc, argv, data))
		return (0);
	if (!alloc_data(data))
		return (0);
	if (!init_forks(data))
		return (0);
	init_philos(data);
	return (1);
}
