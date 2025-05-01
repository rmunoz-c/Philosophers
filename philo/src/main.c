/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 14:26:38 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-15 14:26:38 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo;

	if (!check_args(argc, argv, &data))
	{
		printf("❌ Error: argumentos inválidos\n");
		return (1);
	}
	printf("✅ Argumentos parseados correctamente:\n");
	printf("Número de filósofos:         %u\n", data.n_philos);
	printf("Tiempo para morir (ms):      %lu\n", data.time_to_die);
	printf("Tiempo para comer (ms):      %lu\n", data.time_to_eat);
	printf("Tiempo para dormir (ms):     %lu\n", data.time_to_sleep);
	printf("Veces que debe comer cada uno: ");
	if (data.max_meals == -1)
		printf("no especificado\n");
	else
		printf("%u\n", data.max_meals);
	data.n_philos = 1;
	write (1, "hola\n", 6);
	if (!init_forks(&data) || !init_mutex(&data))
		return (1);
	philo.id = 1;
	philo.s_data = &data;
	if (pthread_create(&philo.thread, NULL, philo_routine, (void *)&philo) != 0)
	{
		write(2, "❌ Error: could not create thread\n", 34);
		return (1);
	}
	pthread_join(philo.thread, NULL);
	return (0);
}
