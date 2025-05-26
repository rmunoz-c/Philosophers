/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 19:30:24 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 19:30:24 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	uint_to_str(unsigned int num, char *dest)
{
	int	len = 0;
	char temp[10];
	int i = 0;
	int j;

	if (num == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
		return (1);
	}
	while (num > 0)
	{
		temp[i++] = (num % 10) + '0';
		num /= 10;
	}
	j = 0;
	while (--i >= 0)
		dest[j++] = temp[i];
	dest[j] = '\0';
	return (j);
}
