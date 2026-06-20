/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enrypt_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:30:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/20 23:53:56 by tel-bouh         ###   ########.fr       */
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

int     ft_check_isit_followed_by_string(t_data *data, int i)
{
        if (i == data->ac - 1)
        {
                ft_display_string_error(data, i);
		return (1);
        }
	return (0);
}

void	ft_hash_str(int f)
{
	ft_putstr_std("hash_str", 1);
	if (f)
		ft_putstr_std("\n", 1);
}

int     ft_encript_string(int i, t_data *data)
{
        printf("----------------------ft_encript_string [%s]----------------------\n", data->av[i]);
	if (data->op.r)
	{
		ft_hash_str(data->op.q);
		if (data->op.q == 0)
			ft_display_str_prefix(i, data);
	}
	else
	{
		if (data->op.q == 0)
			ft_display_str_prefix(i, data);
		ft_hash_str(1);
	}
        data->s_flag_on = 0;
        return (0);
}
