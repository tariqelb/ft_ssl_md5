/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_block_memory_sha.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:31:59 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/07 18:14:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_add_size_to_block_sha256(t_hash_sha256 *sha)
{
	uint64_t	len;
	int			last;
	int			i;

	last = sha->blks_len - 1;
	len = sha->bit_len;
	i = 0;
	if (sha->blks_len == 0)
		return ;
	while (i < 8)
	{
		sha->blocks[last][63 - i] = (len >> (8 * i)) & 0xFF;
		i++;
	}
}

int	ft_allocate_block_memory_sha256(t_hash_sha256 *sha)
{
	size_t	i;

	i = 0;
	sha->blocks = malloc(sizeof(char *) * (sha->blks_len + 1));
	if (!sha->blocks)
		return (1);
	sha->blocks[sha->blks_len] = NULL;
	while (i < sha->blks_len)
	{
		sha->blocks[i] = malloc(64);
		if (!sha->blocks[i])
		{
			ft_free_sha256_i(*sha, i);
			return (1);
		}
		ft_bzero(sha->blocks[i], 64);
		i++;
	}
	return (0);
}
