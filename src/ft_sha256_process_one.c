/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_process_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 01:46:31 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/12 01:47:20 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

uint32_t	ft_rotr(uint32_t x, int n)
{
	return ((x >> n) | (x << (32 - n)));
}

uint32_t	ft_sigma0(uint32_t x)
{
	return (ft_rotr(x, 2) ^ ft_rotr(x, 13) ^ ft_rotr(x, 22));
}

uint32_t	ft_sigma1(uint32_t x)
{
	return (ft_rotr(x, 6) ^ ft_rotr(x, 11) ^ ft_rotr(x, 25));
}

uint32_t	ft_sigma_small0(uint32_t x)
{
	return (ft_rotr(x, 7) ^ ft_rotr(x, 18) ^ (x >> 3));
}

uint32_t	ft_sigma_small1(uint32_t x)
{
	return (ft_rotr(x, 17) ^ ft_rotr(x, 19) ^ (x >> 10));
}
