/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg_round.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 15:07:42 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/09 15:48:38 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_fg_round1(uint32_t *f, uint32_t *g, t_md5_blocks *blks, size_t i)
{
	*f = (blks->b & blks->c) | (~blks->b & blks->d);
	*g = i;
}

void	ft_fg_round2(uint32_t *f, uint32_t *g, t_md5_blocks *blks, size_t i)
{
	*f = (blks->d & blks->b) | (~blks->d & blks->c);
	*g = (5 * i + 1) % 16;
}

void	ft_fg_round3(uint32_t *f, uint32_t *g, t_md5_blocks *blks, size_t i)
{
	*f = blks->b ^ blks->c ^ blks->d;
	*g = (3 * i + 5) % 16;
}

void	ft_fg_round4(uint32_t *f, uint32_t *g, t_md5_blocks *blks, size_t i)
{
	*f = blks->c ^ (blks->b | ~blks->d);
	*g = (7 * i) % 16;
}

void	ft_init_fg_table(t_hash_md5 *md5)
{
	md5->fg_table[0] = ft_fg_round1;
	md5->fg_table[1] = ft_fg_round2;
	md5->fg_table[2] = ft_fg_round3;
	md5->fg_table[3] = ft_fg_round4;
}
