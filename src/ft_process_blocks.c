/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:46:52 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/09 15:51:57 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

/*
static t_fg_func g_fg_table[4] = {
    ft_fg_round1,
    ft_fg_round2,
    ft_fg_round3,
    ft_fg_round4
};
*/

static uint32_t	ft_left_rotate(uint32_t x, uint32_t c)
{
    return (x << c) | (x >> (32 - c));
}

static void	ft_load_block(uint32_t M[16], uint8_t *block)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		M[i] =
			((uint32_t)block[i * 4]) |
			((uint32_t)block[i * 4 + 1] << 8) |
			((uint32_t)block[i * 4 + 2] << 16) |
			((uint32_t)block[i * 4 + 3] << 24);
		i++;
	}
}

static void	ft_process_block(t_hash_md5 *md5, uint32_t M[16])
{
	t_md5_blocks	blks;
	size_t		round;

	ft_init_fg_table(md5);
	blks.a = md5->a;
	blks.b = md5->b;
	blks.c = md5->c;
	blks.d = md5->d;
	md5->i = 0;
	while (md5->i < 64)
	{
		//g_fg_table[round](&md5->f, &md5->g,
		//	blks.b, blks.c, blks.d, md5->i);
		//g_fg_table[round](&md5->f, &md5->g, &blks, md5->i);
		round = md5->i >> 4;
		md5->fg_table[round](&md5->f, &md5->g, &blks, md5->i);
		md5->temp = blks.d;
		md5->x = blks.a + md5->f
			+ md5->k[md5->i] + M[md5->g];
		blks.d = blks.c;
		blks.c = blks.b;
		blks.b = blks.b
			+ ft_left_rotate(md5->x, md5->s[md5->i]);
		blks.a = md5->temp;
		md5->i++;
	}
	md5->a += blks.a;
	md5->b += blks.b;
	md5->c += blks.c;
	md5->d += blks.d;
}

int	ft_process_blocks(t_hash_md5 *md5)
{
	uint32_t	M[16];
	size_t		j;

	j = 0;
	while (j < md5->blks_len)
	{
		ft_load_block(M, md5->blocks[j]);
		ft_process_block(md5, M);
		j++;
	}
	return (0);
}

/*
static uint32_t left_rotate(uint32_t x, uint32_t c)
{
    return (x << c) | (x >> (32 - c));
}

int ft_process_blocks(t_hash_md5 *md5)
{
    uint32_t a, b, c, d;
    uint32_t f, g;
    uint32_t M[16];
    size_t i, j;

    j = 0;

    while (j < md5->blks_len)
    {
        printf("\n===== BLOCK %zu =====\n", j);

        for (i = 0; i < 16; i++)
        {
            M[i] =
                ((uint32_t)(unsigned char)md5->blocks[j][i * 4]) |
                ((uint32_t)(unsigned char)md5->blocks[j][i * 4 + 1] << 8) |
                ((uint32_t)(unsigned char)md5->blocks[j][i * 4 + 2] << 16) |
                ((uint32_t)(unsigned char)md5->blocks[j][i * 4 + 3] << 24);
        }

        a = md5->a;
        b = md5->b;
        c = md5->c;
        d = md5->d;

	for (i = 0; i < 64; i++)
	{
	    if (i < 16)
	    {
		f = (b & c) | (~b & d);
		g = i;
	    }
	    else if (i < 32)
	    {
		f = (d & b) | (~d & c);
		g = (5 * i + 1) % 16;
	    }
	    else if (i < 48)
	    {
		f = b ^ c ^ d;
		g = (3 * i + 5) % 16;
	    }
	    else
	    {
		f = c ^ (b | ~d);
		g = (7 * i) % 16;
	    }

	    uint32_t temp = d;

	    uint32_t x = a + f + md5->k[i] + M[g];

	    d = c;
	    c = b;
	    b = b + left_rotate(x, md5->s[i]);
	    a = temp;
	}
        md5->a += a;
        md5->b += b;
        md5->c += c;
        md5->d += d;

        printf("AFTER BLOCK A=%08x B=%08x C=%08x D=%08x\n",
            md5->a, md5->b, md5->c, md5->d);

        j++;
    }

    return 0;
}
*/
