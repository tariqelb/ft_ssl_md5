/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_sha256_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 00:56:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/07 20:46:53 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_copy_data_to_blocks_file_sha(t_hash_sha256 *sha, t_data *data, int idx)
{
	size_t	pos;
	char	c;
	int		fd;
	int		rd;

	fd = open(data->av[idx], O_RDONLY);
	if (fd < 3)
		return (1);
	pos = 0;
	sha->i = 0;
	sha->j = 0;
	rd = read(fd, &c, 1);
	while (rd == 1)
	{
		sha->blocks[sha->j][pos++] = c;
		if (pos == 64)
		{
			sha->j++;
			pos = 0;
		}
		rd = read(fd, &c, 1);
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
	close(fd);
	return (0);
}

int	ft_initialize_sha_file(t_data *data, t_hash_sha256 *sha, int idx)
{
	sha->str_len = ft_file_len(data->av[idx]);
	sha->bit_len = sha->str_len * 8;
	sha->blks_len = ((sha->str_len + 9 + 63) / 64);
	if (ft_allocate_block_memory_sha256(sha))
		return (0);
	ft_copy_data_to_blocks_file_sha(sha, data, idx);
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
