/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:18:27 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-30 16:18:27 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_args(int argc, char **argv, size_t *val)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!ft_is_str_digit(argv[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < argc)
	{
		if (!ft_atoul(argv[i], &val[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv, t_data *data)
{
	size_t	array[5];

	if (argc < 5 || argc > 6)
		return (write(2, "❌ Error: Wrong number of arguments\n", 36), 0);
	if (!create_args(argc - 1, argv + 1, array))
		return (write(2, "❌ Error: Invalid argument(s)\n", 30), 0);
	if (array[0] == 0 || array[0] > MAX_PHILOS)
		return (write(2, "❌ Error: Invalid number of philosophers\n", 41), 0);
	data->n_philos = array[0];
	data->time_to_die = array[1];
	data->time_to_eat = array[2];
	data->time_to_sleep = array[3];
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = array[4];
	data->stop_simulation = 0;
	data->philos_done = 0;
	return (1);
}
