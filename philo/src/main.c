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
	size_t	i;
	t_data	data;

	if (!check_args(argc, argv, &data))
	{
		write(2, "❌ Error: argumentos inválidos\n", 31);
		return (1);
	}
	if (!init(argc, argv, &data))
		return (1);
	i = 0;
	data.philos[i].born_time = get_time();
	data.philos[i].last_meal = get_time();
	while (i < data.n_philos)
	{
		if (pthread_create(&data.threads[i], NULL,
				philo_routine, (void *)&data.philos[i]) != 0)
		{
			write(2, "❌ Error: no se pudo crear el hilo\n", 35);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data.n_philos)
		pthread_join(data.threads[i++], NULL);
	free_all(&data);
	return (0);
}
