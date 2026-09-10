/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_sha_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:47:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/07 21:02:52 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static void	ft_copy_data_to_blocks_sha_string(t_hash_sha256 *sha,
			t_data *data, int idx)
{
	size_t	pos;
	char	*str;

	str = data->av[idx];
	pos = 0;
	sha->i = 0;
	sha->j = 0;
	while (str[sha->i])
	{
		sha->blocks[sha->j][pos++] = str[sha->i];
		if (pos == 64)
			sha->j++;
		if (pos == 64)
			pos = 0;
		sha->i++;
	}
	if (pos == 64)
	{
		sha->j++;
		pos = 0;
	}
	sha->blocks[sha->j][pos++] = 0x80;
	while (pos < 64)
		sha->blocks[sha->j][pos++] = 0x00;
}

int	ft_initialize_sha_string(t_data *data, t_hash_sha256 *sha, int idx)
{
	//input
	sha->str_len = ft_strlen(data->av[idx]);
	sha->bit_len = sha->str_len * 8;
	sha->blks_len = ((sha->str_len + 9 + 63) / 64);
	if (ft_allocate_block_memory_sha256(sha))
		return (0);
	ft_copy_data_to_blocks_sha_string(sha, data, idx);
	ft_add_size_to_block_sha256(sha);
	sha->a = A_CONST;
	sha->b = B_CONST;
	sha->c = C_CONST;
	sha->d = D_CONST;
	sha->e = E_CONST;
	sha->f = F_CONST;
	sha->g = G_CONST;
	sha->h = H_CONST;
	ft_init_k_sha256(sha->k);
	return (0);
}
