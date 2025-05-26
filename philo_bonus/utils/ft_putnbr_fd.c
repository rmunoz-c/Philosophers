/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 16:30:58 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-16 16:30:58 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

size_t	ft_putnbr_fd(long n, int fd)
{
	size_t	i;

	i = 0;
	if (n == (-__LONG_MAX__) - 1)
	{
		ft_putchar('-');
		ft_putchar('9');
		i += 2;
		n = 223372036854775808;
	}
	if (n < 0)
	{
		ft_putchar('-');
		i ++;
		n = -n;
	}
	if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar((n % 10) + '0');
	return (i + 1);
}
