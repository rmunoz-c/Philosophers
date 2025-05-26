/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:17 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:17 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

static int	run_philos(t_data *data)
{
	size_t	i;

	data->born_time = get_time();
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].last_meal = data->born_time;
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (0);
		if (data->philos[i].pid == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
		i++;
	}
	return (1);
}

int	start_and_wait_monitor(t_data *data)
{
	pthread_t	death_thread;

	if (pthread_create(&death_thread, NULL,
		(void *(*)(void *))monitor_death, (void *)data) != 0)
	{
		write(2, "Error creating monitor_death thread\n", 36);
		cleanup(data);
		return (1);
	}
	if (pthread_join(death_thread, NULL) != 0)
	{
		write(2, "Error joining monitor_death thread\n", 35);
		cleanup(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	
	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]\n", 36);
		exit(1);
	}
	if (!init(argc, argv, &data))
	{
		cleanup(&data);
		return (write(2, "Error during initialization\n", 28), 1);
	}
	if (!run_philos(&data))
	{
		cleanup(&data);
		return (write(2, "Error creating philosopher processes\n", 37), 1);
	}
	if (start_and_wait_monitor(&data) != 0)
		return (1);
	reaper(&data);
	return (0);
}
