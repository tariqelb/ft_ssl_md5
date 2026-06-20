/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enrypt_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:41:52 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/20 23:54:32 by tel-bouh         ###   ########.fr       */
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

void    ft_hash_file(int f) 
{ 
        ft_putstr_std("hash_file",1); 
        if (f) 
                ft_putstr_std("\n", 1); 
}


int     ft_encript_file(int i, t_data *data)
{
	printf("----------------------ft_encript_file [%s]------------------------\n", data->av[i]);
	int	fd;

	fd = open(data->av[i], O_RDONLY);
	if (fd < 3)
	{
		ft_display_file_error(data, i);
		return (1);
	}
	if (data->op.r)
	{
		ft_hash_file(data->op.q);
		if (data->op.q == 0)
			ft_display_file_prefix(i, data);
	}
	else
	{
		if (data->op.q == 0)
			ft_display_file_prefix(i, data);
		ft_hash_file(1);
	}
	close(fd);
	return (0);
}
