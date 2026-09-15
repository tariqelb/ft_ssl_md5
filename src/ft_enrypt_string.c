/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enrypt_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:30:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/15 18:57:25 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_display_string_error(t_data *data, int i)
{
	ft_putstr_std("ft_ssl: ", 2);
	if (data->cmd.cmd_flg == 1)
		ft_putstr_std("md5: ", 2);
	else
		ft_putstr_std("sha256: ", 2);
	ft_putstr_std(data->av[i], 2);
	ft_putstr_std(": missing string argument\n", 2);
	return (1);
}

int	ft_check_isit_followed_by_string(t_data *data, int i)
{
	if (i == data->ac - 1)
	{
		ft_display_string_error(data, i);
		return (1);
	}
	return (0);
}

void	ft_hash_str(int newline, int i, t_data *data)
{
	t_hash_md5	md5;

	if (ft_initialize_md5_args(&md5, data, i))
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

void	ft_hash_str_sha(int newline, int i, t_data *data)
{
	t_hash_sha256	sha;

	if (ft_initialize_sha_string(data, &sha, i))
		return ;
	ft_process_blocks_sha256(&sha);
	ft_print_sha256(&sha);
	if (newline)
		ft_putstr_std("\n", 1);
	ft_free_sha256(sha);
}

int	ft_encript_string(int i, t_data *data)
{
	if (data->op.r)
	{
		data->str[data->cmd.cmd_flg - 1](data->op.q, i, data);
		if (data->op.q == 0)
			ft_display_str_prefix(i, data);
	}
	else
	{
		if (data->op.q == 0)
			ft_display_str_prefix(i, data);
		data->str[data->cmd.cmd_flg - 1](1, i, data);
	}
	data->s_flag_on = 0;
	return (0);
}
