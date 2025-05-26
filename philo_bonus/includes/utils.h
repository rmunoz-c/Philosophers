/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 16:00:35 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-05-26 16:00:35 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

size_t	ft_atoul(const char *n, unsigned long *val);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_exit(void *ptr);
int		ft_is_str_digit(char *s);
int		ft_putstr(char *s);
int		ft_putchar(int c);
int		ft_put_hex_ptr(size_t n, const char format, int is_ptr);
int		ft_printf(char const *s, ...);
size_t	ft_putnbr_fd(long n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif