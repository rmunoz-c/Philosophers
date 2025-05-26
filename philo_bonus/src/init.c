/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:07 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:07 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	sem_unlink_all(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/log_lock_sem");
	sem_unlink("/stop_lock_sem");
	sem_unlink("/philos_full_sem");
}

int	alloc_data(t_data *data)
{
	data->philos = ft_calloc(data->n_philos, sizeof(t_philo));
	if (!data->philos)
		return (0);
	return (1);
}

int	init_semaphores(t_data *data)
{
	sem_unlink_all();
	data->forks = sem_open("/forks_sem", O_CREAT, 0644, data->n_philos);
	if (data->forks == SEM_FAILED)
		return (write(2, "❌Error initializing forks semaphore\n", 39), 0);
	data->log_lock = sem_open("/log_lock_sem", O_CREAT, 0644, 1);
	if (data->log_lock == SEM_FAILED)
		return (write(2, "❌Error initializing log_lock semaphore\n", 42), 0);
	data->stop_lock = sem_open("/stop_lock_sem", O_CREAT, 0644, 1);
	if (data->stop_lock == SEM_FAILED)
		return (write(2, "❌Error initializing stop_lock semaphore\n", 43), 0);
	data->philos_full = sem_open("/philos_full_sem", O_CREAT, 0644, 0);
	if (data->philos_full == SEM_FAILED)
		return (write(2, "❌Error init philos_full semaphore\n", 44), 0);
	return (1);
}

void	init_philos(t_data *data)
{
	size_t	i;
	char	sem_name[64];

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].s_data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].pid = 0;
		sprintf(sem_name, "/meal_lock_%zu", i + 1);
		sem_unlink(sem_name);
		data->philos[i].meal_lock = sem_open(sem_name, O_CREAT, 0644, 1);
		i++;
	}
}

int	init(int argc, char **argv, t_data *data)
{
	if (!check_args(argc, argv, data))
		return (0);
	if (!alloc_data(data))
		return (0);
	if (!init_semaphores(data))
		return (0);
	init_philos(data);
	return (1);
}
