/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_md5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 00:01:54 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/26 01:28:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_add_size_to_block(t_hash_md5 *md5)
{
	uint64_t	len;
	int		last;
	int 		i;

	last = md5->blks_len - 1;
	len = md5->bit_len;
	i = 0;
	if (md5->blks_len == 0)
	    return ;
	while (i < 8)
	{
	    md5->blocks[last][56 + i] = (uint8_t)((len >> (8 * i)) & 0xFF);
	    i++;
	}
}

void	ft_copy_data_to_blocks(t_hash_md5 *md5, t_data *data, int idx)
{
	size_t pos;
	char *str;

	str = data->av[idx];
	pos = 0;
	md5->i = 0;
	md5->j = 0;
	while (str[md5->i])
	{
		md5->blocks[md5->j][pos++] = str[md5->i];
		if (pos == 64)
		{
			md5->j++;
			pos = 0;
		}
		md5->i++;
	}
	if (pos == 64)
	{
		md5->j++;
		pos = 0;
	}
	md5->blocks[md5->j][pos++] = 0x80;
	while (pos < 64)
		md5->blocks[md5->j][pos++] = 0x00;
}

int	ft_allocate_block_memory(t_hash_md5 *md5)
{
	size_t	i;

	i = 0;
	md5->blocks = malloc(sizeof(char *) * (md5->blks_len + 1));
	if (!md5->blocks)
	    return (1);
	md5->blocks[md5->blks_len] = NULL;
	while (i < md5->blks_len)
	{
		md5->blocks[i] = malloc(64);
		if (!md5->blocks[i])
		{
			//ft_free();
			return (1);
		}
		ft_bzero(md5->blocks[i], 64);
		i++;
	}
	return (0);
}

int ft_initialize_md5_args(t_hash_md5 *md5, t_data *data, int i)
{
	md5->str_len = ft_strlen(data->av[i]);
	md5->bit_len = md5->str_len * 8;
	md5->blks_len = (md5->str_len + 9) / 64 + 1;
	if (ft_allocate_block_memory(md5))
	    return (1);
	ft_copy_data_to_blocks(md5, data, i);
	ft_add_size_to_block(md5);
	md5->a = A_CONS;
	md5->b = B_CONS;
	md5->c = C_CONS;
	md5->d = D_CONS;
	ft_init_k(md5->k);
	ft_init_s(md5->s);
	return (0);
}
