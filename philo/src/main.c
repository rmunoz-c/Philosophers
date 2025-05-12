/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:26:38 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/05/12 20:48:36 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"
#include <stdio.h>

void	p_new(t_data *data, t_philo **dinner, pthread_t **philo)
{
	size_t	n;

	n = data->n_philos;
	data->forks = malloc(n * sizeof(pthread_mutex_t));
	if (!data->forks)
		ft_free_exit(data->forks);
	*dinner = malloc(n * sizeof(t_philo));
	if (!*dinner)
		ft_free_exit(data->forks);
	*philo = malloc(n * sizeof(pthread_t));
	if (!*philo)
	{
		free(data->forks);
		ft_free_exit(*dinner);
	}
}

void	run_simulation(t_data *data, t_philo *philos, pthread_t *threads)
{
	size_t		i;
	uint64_t	start_time;

	start_time = get_time();
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].born_time = start_time;
		philos[i].last_meal = start_time;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
		{
			p_free(data, philos, threads);
			return ;
		}
		i++;
	}
	reaper(data);
	i = 0;
	while (i < data->n_philos)
	{
		if (philos[i].is_alive)
			pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*dinner;
	pthread_t	*threads;

	dinner = NULL;
	threads = NULL;
	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	check_args(argc, argv, &data);
	p_new(&data, &dinner, &threads);
	if (!init_mutex(&data))
		return (p_free(&data, dinner, threads), 1);
	if (!init_forks(&data))
		return (p_free(&data, dinner, threads), 1);
	run_simulation(&data, dinner, threads);
	p_free(&data, dinner, threads);
	return (0);
}
