/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 17:51:46 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 17:51:46 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->s_data->forks);
	log_action(philo, "has taken a fork");
	sem_wait(philo->s_data->forks);
	log_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->s_data->forks);
	sem_post(philo->s_data->forks);
}

void	eat_routine(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time();
	log_action(philo, "is eating");
	sem_post(philo->meal_lock);
	usleep_control(philo->s_data->time_to_eat, philo);
	philo->meals_eaten++;
}
