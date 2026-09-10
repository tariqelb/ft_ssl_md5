/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_message_shedule.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:25:30 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/07 18:16:21 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_build_w(uint32_t w[64], uint8_t *block)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		w[i] = ((uint32_t)block[i * 4] << 24)
			| ((uint32_t)block[i * 4 + 1] << 16)
			| ((uint32_t)block[i * 4 + 2] << 8)
			| ((uint32_t)block[i * 4 + 3]);
		i++;
	}
	while (i < 64)
	{
		w[i] = sigma1(w[i - 2])
			+ w[i - 7]
			+ sigma0(w[i - 15])
			+ w[i - 16];
		i++;
	}
}
