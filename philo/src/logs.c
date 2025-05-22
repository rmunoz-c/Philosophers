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
	time = time - philo->born_time;
	if (!get_stop_simulation(philo->s_data))
	{
		if (equip)
			printf("\033[1;33m%lu %u has taken a fork\033[0m\n",
				time, philo->id);
		else
			printf("\033[1;35m%lu %u has dropped a fork\033[0m\n",
				time, philo->id);
	}
}

void	eat_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("\033[1;32m%lu %u is eating\033[0m\n", time, philo->id);
}

void	sleep_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("\033[1;36m%lu %u is sleeping\033[0m\n", time, philo->id);
}

void	think_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("\033[1;34m%lu %u is thinking\033[0m\n", time, philo->id);
}

void	death_log(t_philo *philo)
{
	uint64_t	time;

	time = get_time();
	time = time - philo->born_time;
	if (!get_stop_simulation(philo->s_data))
		printf("\033[1;31m%lu %u died\033[0m\n", time, philo->id);
}
