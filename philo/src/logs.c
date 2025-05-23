/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 15:47:32 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-01 15:47:32 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fork_log(t_philo *philo, size_t equip)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->s_data->born_time;
	if (!get_stop_simulation(philo->s_data))
	{
		if (equip)
			printf("%lu %u has taken a fork\n",
				time, philo->id);
	}
}

void	eat_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->s_data->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("%lu %u is eating\n", time, philo->id);
}

void	sleep_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->s_data->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("%lu %u is sleeping\n", time, philo->id);
}

void	think_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->s_data->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("%lu %u is thinking\n", time, philo->id);
}

void	death_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->s_data->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("%lu %u died\n", time, philo->id);
}
