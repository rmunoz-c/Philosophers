/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:02 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:02 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	kill_all_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGTERM);
		i++;
	}
}

static void	cleanup_philo_semaphores(t_data *data)
{
	size_t	i;
	char	sem_name[64];

	if (!data->philos)
		return ;
	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos[i].meal_lock)
		{
			sem_close(data->philos[i].meal_lock);
			sprintf(sem_name, "/meal_lock_%zu", i + 1);
			sem_unlink(sem_name);
		}
		i++;
	}
}

static void	cleanup_global_semaphores(t_data *data)
{
	if (data->forks)
	{
		sem_close(data->forks);
		sem_unlink("/forks_sem");
	}
	if (data->log_lock)
	{
		sem_close(data->log_lock);
		sem_unlink("/log_lock_sem");
	}
	if (data->stop_lock)
	{
		sem_close(data->stop_lock);
		sem_unlink("/stop_lock_sem");
	}
	if (data->philos_full)
	{
		sem_close(data->philos_full);
		sem_unlink("/philos_full_sem");
	}
}

void	cleanup(t_data *data)
{
	if (data->philos)
	{
		cleanup_philo_semaphores(data);
		free(data->philos);
		data->philos = NULL;
	}
	cleanup_global_semaphores(data);
}

int	get_stop_simulation(t_data *data)
{
	int	stop;

	sem_wait(data->stop_lock);
	stop = data->stop_simulation;
	sem_post(data->stop_lock);
	return (stop);
}
