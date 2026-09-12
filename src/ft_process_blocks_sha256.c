/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_blocks_sha256.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:36:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/12 01:52:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_init_sha256_bkls(t_sha_bkls *bkls, t_hash_sha256 *sha)
{
	bkls->a = sha->a;
	bkls->b = sha->b;
	bkls->c = sha->c;
	bkls->d = sha->d;
	bkls->e = sha->e;
	bkls->f = sha->f;
	bkls->g = sha->g;
	bkls->h = sha->h;
}

void	ft_sha256_round(t_sha_bkls *bkls, t_hash_sha256 *sha, size_t j)
{
	bkls->t1 = bkls->h + ft_sigma1(bkls->e)
		+ ft_ch(bkls->e, bkls->f, bkls->g)
		+ sha->k[j] + bkls->w[j];
	bkls->t2 = ft_sigma0(bkls->a) + ft_maj(bkls->a, bkls->b, bkls->c);
	bkls->h = bkls->g;
	bkls->g = bkls->f;
	bkls->f = bkls->e;
	bkls->e = bkls->d + bkls->t1;
	bkls->d = bkls->c;
	bkls->c = bkls->b;
	bkls->b = bkls->a;
	bkls->a = bkls->t1 + bkls->t2;
}

void	ft_process_sha256_rounds(t_sha_bkls *bkls, t_hash_sha256 *sha)
{
	size_t	j;

	j = 0;
	while (j < 64)
	{
		ft_sha256_round(bkls, sha, j);
		j++;
	}
}

void	ft_update_sha256_hash(t_sha_bkls *bkls, t_hash_sha256 *sha)
{
	sha->a += bkls->a;
	sha->b += bkls->b;
	sha->c += bkls->c;
	sha->d += bkls->d;
	sha->e += bkls->e;
	sha->f += bkls->f;
	sha->g += bkls->g;
	sha->h += bkls->h;
}

void	ft_process_blocks_sha256(t_hash_sha256 *sha)
{
	t_sha_bkls	bkls;
	size_t		i;

	i = 0;
	while (i < sha->blks_len)
	{
		ft_build_w(bkls.w, sha->blocks[i]);
		ft_init_sha256_bkls(&bkls, sha);
		ft_process_sha256_rounds(&bkls, sha);
		ft_update_sha256_hash(&bkls, sha);
		i++;
	}
}

/*
void    ft_process_blocks_sha256(t_hash_sha256 *sha)
{
	uint32_t    w[64];
	uint32_t    a, b, c, d, e, f, g, h;
	uint32_t    t1, t2;
	size_t      i;
	size_t      j;

	i = 0;
	while (i < sha->blks_len)
	{
	    // 1. Build message schedule
	    ft_build_w(w, sha->blocks[i]);

	    // 2. Initialize working variables
	    a = sha->a;
	    b = sha->b;
	    c = sha->c;
	    d = sha->d;
	    e = sha->e;
	    f = sha->f;
	    g = sha->g;
	    h = sha->h;

	    // 3. Main loop (64 rounds)
	    j = 0;
	    while (j < 64)
	    {
		t1 = h + SIGMA1(e) + Ch(e, f, g) + sha->k[j] + w[j];
		t2 = SIGMA0(a) + Maj(a, b, c);

		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;

		j++;
	    }

	    // 4. Add compressed chunk to current hash
	    sha->a += a;
	    sha->b += b;
	    sha->c += c;
	    sha->d += d;
	    sha->e += e;
	    sha->f += f;
	    sha->g += g;
	    sha->h += h;

	    i++;
	}
}
*/
