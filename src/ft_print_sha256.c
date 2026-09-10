/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sha256.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:08:41 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/09 20:37:21 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static void	ft_putchar_hex(uint8_t byte)
{
	char	*hex;
	char	out[2];

	hex = "0123456789abcdef";
	out[0] = hex[(byte >> 4) & 0xF];
	out[1] = hex[byte & 0xF];
	write(1, out, 2);
}

static void	ft_print_word_be(uint32_t x)
{
	ft_putchar_hex((x >> 24) & 0xFF);
	ft_putchar_hex((x >> 16) & 0xFF);
	ft_putchar_hex((x >> 8) & 0xFF);
	ft_putchar_hex(x & 0xFF);
}

void	ft_print_sha256(t_hash_sha256 *sha)
{
	ft_print_word_be(sha->a);
	ft_print_word_be(sha->b);
	ft_print_word_be(sha->c);
	ft_print_word_be(sha->d);
	ft_print_word_be(sha->e);
	ft_print_word_be(sha->f);
	ft_print_word_be(sha->g);
	ft_print_word_be(sha->h);
}
