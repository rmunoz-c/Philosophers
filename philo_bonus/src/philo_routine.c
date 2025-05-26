/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:52:33 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:52:33 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	sleep_and_think(t_philo *philo)
{
	log_action(philo, "is sleeping");
	usleep_control(philo->s_data->time_to_sleep, philo);
	log_action(philo, "is thinking");
}

static void	check_death(t_philo *philo)
{
	uint64_t	now;

	sem_wait(philo->meal_lock);
	now = get_time();
	if ((now - philo->last_meal) > philo->s_data->time_to_die)
	{
		log_action(philo, "died");
		set_stop_simulation(philo->s_data, 1);
		sem_post(philo->meal_lock);
		exit(1);
	}
	sem_post(philo->meal_lock);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep_control(philo->s_data->time_to_eat / 2, philo);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		check_death(philo);
		put_forks(philo);
		if (philo->s_data->max_meals != -1
			&& philo->meals_eaten >= philo->s_data->max_meals)
		{
			sem_post(philo->s_data->philos_full);
			exit(0);
		}
		sleep_and_think(philo);
		check_death(philo);
	}
}
