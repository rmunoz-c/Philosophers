/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:43 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:43 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	usleep_control(__useconds_t time_in_ms, t_philo *philo)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		if (get_stop_simulation(philo->s_data))
			break;
		usleep(500);
	}
}

