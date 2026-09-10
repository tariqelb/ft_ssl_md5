/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_blocks_sha256.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:36:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/07/09 18:48:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

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
