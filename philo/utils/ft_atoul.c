/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:39:57 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-30 16:39:57 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

size_t	ft_atoul(const char *n, unsigned long *val)
{
	size_t	count;
	size_t	result;

	count = 0;
	result = 0;
	while (n[count] == ' ' || (n[count] >= 9 && n[count] <= 13))
		count++;
	while (n[count])
	{
		result = result * 10 + (n[count++] - '0');
		if (result > ULONG_MAX)
			return (0);
	}
	if (result == 0)
		return (0);
	*val = (int)result;
	return (1);
}
