/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_hash_sha256.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:14:24 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/09 20:42:57 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_display_hash_sha256(t_data *data)
{
	t_hash_sha256	sha;

	if (ft_initialize_sha256_stdin(data, &sha))
		return (0);
	ft_process_blocks_sha256(&sha);
	ft_print_sha256(&sha);
	ft_putstr_std("\n", 1);
	ft_free_sha256(sha);
	return (0);
}
