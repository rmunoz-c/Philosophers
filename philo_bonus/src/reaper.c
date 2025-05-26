/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:38 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:38 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_stop_simulation(t_data *data, int value)
{
	sem_wait(data->stop_lock);
	data->stop_simulation = value;
	sem_post(data->stop_lock);
}

static int	all_philos_done(t_data *data)
{
	int	value;

	value = 0;
	sem_wait(data->philos_full);
	sem_getvalue(data->philos_full, &value);
	return (value >= (int)data->n_philos);
}

void	reaper(t_data *data)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_all_philos(data);
				break ;
			}
			else if (WEXITSTATUS(status) == 0)
			{
				if (all_philos_done(data))
					break ;
			}
		}
	}
	cleanup(data);
}

static int	check_philo_death(t_data *data, unsigned int i)
{
	uint64_t	now;

	sem_wait(data->philos[i].meal_lock);
	now = get_time();
	if ((now - data->philos[i].last_meal) > data->time_to_die)
	{
		log_action(&data->philos[i], "died");
		set_stop_simulation(data, 1);
		kill_all_philos(data);
		sem_post(data->philos[i].meal_lock);
		return (1);
	}
	sem_post(data->philos[i].meal_lock);
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data			*data;
	unsigned int	i;

	data = (t_data *)arg;
	while (!get_stop_simulation(data))
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}


