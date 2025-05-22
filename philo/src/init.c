/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:47:56 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:47:56 by rmunoz-c         ###   ########.fr       */
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
	data->philos = ft_calloc(data->n_philos, sizeof(t_philo));
	data->threads = ft_calloc(data->n_philos, sizeof(pthread_t));
	data->forks = ft_calloc(data->n_philos, sizeof(pthread_mutex_t));
	if (!data->philos || !data->threads || !data->forks)
	{
		free(data->philos);
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
		data->philos[i].right_fork = &data->forks[(i + data->n_philos - 1)
			% data->n_philos];
		i++;
	}
	return (1);
}

void	init_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].s_data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].is_alive = 1;
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
		{
			write(2, "❌ Error initializing last_meal_mutex\n", 38);
			exit(EXIT_FAILURE);
		}
		if (pthread_mutex_init(&data->philos[i].is_alive_mutex, NULL) != 0)
		{
			write(2, "❌ Error initializing is_alive_mutex\n", 37);
			exit(EXIT_FAILURE);
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
