/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_sha256_stdin.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:19:20 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 02:33:32 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"
/*
	// 1. Copy message
	while (str[sha->i])
	// 2. Append 0x80
	sha->blocks[sha->j][pos++] = 0x80;
	// 3. If no space for length → new block
	if (pos > 56)
	// 4. Pad with zeros until byte 56
	while (pos < 56)

*/

static void	ft_pad_blocks_sha_stdin(t_hash_sha256 *sha, size_t pos)
{
	sha->blocks[sha->j][pos++] = 0x80;
	if (pos > 56)
	{
		while (pos < 64)
			sha->blocks[sha->j][pos++] = 0x00;
		sha->j++;
		pos = 0;
	}
	while (pos < 56)
		sha->blocks[sha->j][pos++] = 0x00;
}

static void	ft_copy_data_to_blocks_sha_stdin(t_hash_sha256 *sha,
		t_data *data)
{
	size_t	pos;
	char	*str;

	str = data->args[0].str;
	pos = 0;
	sha->i = 0;
	sha->j = 0;
	while (str[sha->i])
	{
		sha->blocks[sha->j][pos++] = str[sha->i++];
		if (pos == 64)
		{
			sha->j++;
			pos = 0;
		}
	}
	ft_pad_blocks_sha_stdin(sha, pos);
}

int	ft_initialize_sha256_stdin(t_data *data, t_hash_sha256 *sha)
{
	sha->str_len = ft_strlen(data->args[0].str);
	sha->bit_len = sha->str_len * 8;
	sha->blks_len = ((sha->str_len + 9 + 63) / 64);
	if (ft_allocate_block_memory_sha256(sha))
		return (0);
	ft_copy_data_to_blocks_sha_stdin(sha, data);
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
