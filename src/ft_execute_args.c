/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:32:56 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 01:49:33 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	ft_display_hash(t_data *data)
{
	t_hash_md5	md5;

	if (ft_initialize_md5_stdin(&md5, data))
		return ;
	ft_process_blocks(&md5);
	ft_print_word(md5.a);
	ft_print_word(md5.b);
	ft_print_word(md5.c);
	ft_print_word(md5.d);
	ft_putstr_std("\n", 1);
	ft_free_md5(md5);
}

void	ft_execute_stdin(t_data *data)
{
	ft_display_prefix(data);
	if (data->cmd.cmd_flg == 1)
		ft_display_hash(data);
	else
		ft_display_hash_sha256(data);
}

int	ft_parse_arg_and_exec(int i, t_data *data)
{
	if (RANDOM && ft_is_one_global_option(i, data))
		return (0);
	else if (RANDOM == 0 && ft_is_one_global_option(i, data)
		&& data->str_muted != -1 && i < data->str_muted)
		return (0);
	else if (RANDOM == 0 && ft_is_one_global_option(i, data)
		&& data->str_muted == -1)
		return (0);
	else if (ft_check_is_string_flag(i, data))
	{
		if (data->str_muted == -1 || i < data->str_muted)
		{
			ft_check_isit_followed_by_string(data, i);
			return (0);
		}
		if (i > data->str_muted)
			data->s_flag_on = 0;
	}
	if (data->s_flag_on)
		ft_encript_string(i, data);
	else
		ft_encript_file(i, data);
	return (0);
}

int	ft_execute_args(t_data *data)
{
	int	i;

	i = 2;
	if (data->args && data->args[0].type == 0)
		ft_execute_stdin(data);
	while (i < data->ac)
	{
		ft_parse_arg_and_exec(i, data);
		i++;
	}
	return (0);
}
