/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 16:38:56 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-04-16 16:38:56 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	ft_conver(va_list args, const char format)
{
	int		len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		len += ft_put_hex_ptr((size_t)va_arg(args, void *), 'x', 1);
	else if (format == 'd' || format == 'i')
		len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (format == 'u')
		len += ft_putnbr_fd(va_arg(args, unsigned int), 1);
	else if (format == 'x')
		len += ft_put_hex_ptr(va_arg(args, unsigned int), 'x', 0);
	else if (format == 'X')
		len += ft_put_hex_ptr(va_arg(args, unsigned int), 'X', 0);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(char const *s, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += ft_conver(args, s[i + 1]);
			i++;
		}
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (len);
}
