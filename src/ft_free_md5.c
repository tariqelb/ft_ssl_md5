/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 01:28:54 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 02:24:39 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_free_md5_i(t_hash_md5 md5, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (md5.blocks[j] != NULL)
			free(md5.blocks[j]);
		j++;
	}
	if (md5.blocks != NULL)
		free(md5.blocks);
}

void	ft_free_md5(t_hash_md5 md5)
{
	size_t	j;

	j = 0;
	while (j < md5.blks_len)
	{
		if (md5.blocks[j] != NULL)
			free(md5.blocks[j]);
		j++;
	}
	if (md5.blocks != NULL)
		free(md5.blocks);
}

void	ft_free_sha256_i(t_hash_sha256 sha, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (sha.blocks[j] != NULL)
			free(sha.blocks[j]);
		j++;
	}
	if (sha.blocks != NULL)
		free(sha.blocks);
}

void	ft_free_sha256(t_hash_sha256 sha)
{
	size_t	j;

	j = 0;
	while (j < sha.blks_len)
	{
		if (sha.blocks[j] != NULL)
			free(sha.blocks[j]);
		j++;
	}
	if (sha.blocks != NULL)
		free(sha.blocks);
}

void	ft_free_data_stdin(t_data data)
{
	if (data.args != NULL)
	{
		if (data.args[0].str != NULL)
			free(data.args[0].str);
		free(data.args);
	}
}
