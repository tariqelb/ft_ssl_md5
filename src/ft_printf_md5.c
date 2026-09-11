/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 02:16:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 02:35:05 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static void	ft_print_uint32(uint32_t n)
{
	uint8_t	*p;
	int		i;

	p = (uint8_t *)&n;
	i = 0;
	while (i < 4)
	{
		printf("%02x", p[i]);
		i++;
	}
}

void	ft_print_md5(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	ft_print_uint32(a);
	ft_print_uint32(b);
	ft_print_uint32(c);
	ft_print_uint32(d);
}

static void	ft_putchar_hex(uint8_t byte)
{
	char	*hex;
	char	out[2];

	hex = "0123456789abcdef";
	out[0] = hex[(byte >> 4) & 0xF];
	out[1] = hex[byte & 0xF];
	write(1, out, 2);
}

void	ft_print_word(uint32_t x)
{
	ft_putchar_hex(x & 0xFF);
	ft_putchar_hex((x >> 8) & 0xFF);
	ft_putchar_hex((x >> 16) & 0xFF);
	ft_putchar_hex((x >> 24) & 0xFF);
}
