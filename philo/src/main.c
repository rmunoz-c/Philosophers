/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 14:47:25 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-20 14:47:25 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void	run_simulation(t_data *data, t_philo *philos, pthread_t *threads)
{
	size_t		i;
	uint64_t	start_time;
	pthread_t	reaper_thread;

	start_time = get_time();
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].born_time = start_time;
		philos[i].last_meal = start_time;
		pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&reaper_thread, NULL, reaper, data);
	i = 0;
	while (i < data->n_philos)
		pthread_join(threads[i++], NULL);
	pthread_join(reaper_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	if (!init(argc, argv, &data))
		return (write(2, "Error during initialization\n", 28), 1);
	if (!init_mutex(&data))
		return (free_all(&data), 1);
	run_simulation(&data, data.philos, data.threads);
	free_all(&data);
	return (0);
}
