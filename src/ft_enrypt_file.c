/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enrypt_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:41:52 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/15 18:56:12 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_display_file_error(t_data *data, int i)
{
	ft_putstr_std("ft_ssl: ", 2);
	if (data->cmd.cmd_flg == 1)
		ft_putstr_std("md5: ", 2);
	else
		ft_putstr_std("sha256: ", 2);
	ft_putstr_std(data->av[i], 2);
	ft_putstr_std(": No such file or directory\n", 2);
	return (1);
}

void	ft_hash_file(int newline, int i, t_data *data)
{
	t_hash_md5	md5;

	if (ft_initialize_md5_file(&md5, data, i))
		return ;
	ft_process_blocks(&md5);
	ft_print_word(md5.a);
	ft_print_word(md5.b);
	ft_print_word(md5.c);
	ft_print_word(md5.d);
	if (newline)
		ft_putstr_std("\n", 1);
	ft_free_md5(md5);
}

void	ft_hash_file_sha(int newline, int i, t_data *data)
{
	t_hash_sha256	sha;

	if (ft_initialize_sha_file(data, &sha, i))
		return ;
	ft_process_blocks_sha256(&sha);
	ft_print_sha256(&sha);
	if (newline)
		ft_putstr_std("\n", 1);
	ft_free_sha256(sha);
}

int	ft_encript_file(int i, t_data *data)
{
	int	fd;

	fd = open(data->av[i], O_RDONLY);
	if (fd < 3)
		return (ft_display_file_error(data, i));
	if (data->op.r)
	{
		data->file[data->cmd.cmd_flg - 1](data->op.q, i, data);
		if (data->op.q == 0)
			ft_display_file_prefix(i, data);
	}
	else
	{
		if (data->op.q == 0)
			ft_display_file_prefix(i, data);
		data->file[data->cmd.cmd_flg - 1](1, i, data);
	}
	close(fd);
	return (0);
}
