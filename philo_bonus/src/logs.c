/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:12 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:12 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	log_action(t_philo *philo, const char *msg)
{
	uint64_t	time;

	sem_wait(philo->s_data->log_lock);
	if (!get_stop_simulation(philo->s_data))
	{
		time = get_time() - philo->s_data->born_time;
		printf("%lu %u %s\n", time, philo->id, msg);
	}
	sem_post(philo->s_data->log_lock);
}
