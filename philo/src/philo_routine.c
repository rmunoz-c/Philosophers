/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 18:31:50 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-30 18:31:50 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("🧠 Filósofo %u ha comenzado su rutina\n", philo->id);
	while (1)
	{
		printf("Filósofo %u está pensando...\n", philo->id);
		usleep(philo->s_data->time_to_sleep);
		printf("Filósofo %u está comiendo...\n", philo->id);
        usleep(philo->s_data->time_to_eat);
		printf("Filósofo %d está durmiendo...\n", philo->id);
		usleep(philo->s_data->time_to_sleep);
	}
	return (NULL);
}