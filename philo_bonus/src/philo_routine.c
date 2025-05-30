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
	uint64_t	last_meal;

	sem_wait(philo->meal_lock);
	last_meal = philo->last_meal;
	sem_post(philo->meal_lock);

	now = get_time();
	if ((now - last_meal) > philo->s_data->time_to_die)
	{
		log_action(philo, "died");
		set_stop_simulation(philo->s_data, 1);
		exit(1);
	}
}


void	philo_routine(t_philo *philo)
{
	if (philo->id % 2)
		usleep_control(philo->s_data->time_to_eat / 2, philo);
	while (1)
	{
		take_forks(philo);
		eat_routine(philo);
		check_death(philo);
		drop_forks(philo);
		if (philo->s_data->max_meals != -1
			&& philo->meals_eaten >= philo->s_data->max_meals)
		{
			sem_post(philo->s_data->philos_full);
			exit(0);
		}
		sleep_and_think(philo);
		usleep_control(1, philo);
		check_death(philo);
	}
}
