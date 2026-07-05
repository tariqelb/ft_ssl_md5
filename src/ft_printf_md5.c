/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 02:16:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/26 01:26:01 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_print_md5(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    uint8_t *p;

    p = (uint8_t *)&a;
    for (int i = 0; i < 4; i++)
        printf("%02x", p[i]);

    p = (uint8_t *)&b;
    for (int i = 0; i < 4; i++)
        printf("%02x", p[i]);

    p = (uint8_t *)&c;
    for (int i = 0; i < 4; i++)
        printf("%02x", p[i]);

    p = (uint8_t *)&d;
    for (int i = 0; i < 4; i++)
        printf("%02x", p[i]);
}

static void ft_putchar_hex(uint8_t byte)
{
    char *hex = "0123456789abcdef";
    char out[2];

    out[0] = hex[(byte >> 4) & 0xF];
    out[1] = hex[byte & 0xF];
    write(1, out, 2);
}

void ft_print_word(uint32_t x)
{
    ft_putchar_hex(x & 0xFF);
    ft_putchar_hex((x >> 8) & 0xFF);
    ft_putchar_hex((x >> 16) & 0xFF);
    ft_putchar_hex((x >> 24) & 0xFF);
}
