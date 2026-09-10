/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_md5_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 01:37:58 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/07 20:42:35 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_file_len(char *av)
{
	int		size;
	int		fd;
	int		rd;
	char	c;

	size = 0;
	fd = open(av, O_RDONLY);
	if (fd < 3)
		return (size);
	rd = read(fd, &c, 1);
	while (rd == 1)
	{
		size++;
		rd = read(fd, &c, 1);
	}
	close(fd);
	return (size);
}

int	ft_copy_data_to_blocks_file(t_hash_md5 *md5, t_data *data, int idx)
{
	size_t	pos;
	char	c;
	int		fd;
	int		rd;

	fd = open(data->av[idx], O_RDONLY);
	if (fd < 3)
		return (1);
	pos = 0;
	md5->i = 0;
	md5->j = 0;
	rd = read(fd, &c, 1);
	while (rd == 1)
	{
		md5->blocks[md5->j][pos++] = c;
		if (pos == 64)
		{
			md5->j++;
			pos = 0;
		}
		rd = read(fd, &c, 1);
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
	close(fd);
	return (0);
}

int	ft_initialize_md5_file(t_hash_md5 *md5, t_data *data, int i)
{
	md5->str_len = ft_file_len(data->av[i]);
	md5->bit_len = md5->str_len * 8;
	md5->blks_len = (md5->str_len + 9) / 64 + 1;
	if (ft_allocate_block_memory(md5))
		return (1);
	if (ft_copy_data_to_blocks_file(md5, data, i))
		return (1);
	ft_add_size_to_block(md5);
	md5->a = A_CONS;
	md5->b = B_CONS;
	md5->c = C_CONS;
	md5->d = D_CONS;
	ft_init_k(md5->k);
	ft_init_s(md5->s);
	return (0);
}
