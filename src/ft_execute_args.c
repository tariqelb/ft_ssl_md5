/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:32:56 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/18 02:54:04 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	ft_display_hash(t_data *data)
{
	ft_putstr_std("hash\n", 1);
	if (data->op.r == 0)
		ft_putstr_std("\n", 1);
}

void	ft_execute_stdin(t_data *data)
{
	if (data->op.r == 0)
		ft_display_prefix(data);
	ft_display_hash(data);
}

int	ft_parse_arg_and_exec(int i, t_data *data)
{
	//printf("before :opt (%s) i {%d} random : [%d] str_muted (%d) s_flag {%d}\n", data->av[i], i, RANDOM, data->str_muted, data->s_flag_on);
	if (RANDOM && ft_is_one_global_option(i, data))
		return (0);
	else if (RANDOM == 0 && ft_is_one_global_option(i, data) && i < data->str_muted)
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
	//printf("opt (%s) i {%d} random : [%d] str_muted (%d) s_flag {%d}\n", data->av[i], i, RANDOM, data->str_muted, data->s_flag_on);
	return (0);
}

int	ft_execute_args(t_data *data)
{
	printf("ft_execute_args\n");
	int	i;

	i = 2;
	if (data->op.p)
		ft_execute_stdin(data);
	while (i < data->ac)
	{
		ft_parse_arg_and_exec(i, data);
		i++;
	}
	return (0);
}
