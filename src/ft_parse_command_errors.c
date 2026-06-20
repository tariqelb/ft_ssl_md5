/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command_errors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:40:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/20 18:57:35 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_parse_command_errors(int ac, char **av, t_data *data)
{
	//printf("ft_parse_commad_errors %d %s\n", ac, av[0]);
	if (ac == 1)
	{
		ft_putstr_std("usage: ft_ssl command [flags] [file/string]\n", 2);
		return (1);
	}
	if (ft_strcmp(av[1], "md5") != 0 && ft_strcmp(av[1], "sha256") != 0)
	{
		ft_putstr_std("ft_ssl: Error: '", 2);
		ft_putstr_std(av[1], 2);
		ft_putstr_std("' is an invalid command.\n\n", 2);
		ft_putstr_std("Commands:\nmd5\nsha256\n\n", 2);
		ft_putstr_std("Flags:\n-p -q -r -s\n", 2);
		return (1);
	}
	if (ft_strcmp(av[1], "md5") == 0)
		data->cmd.cmd_flg = 1;
	else if (ft_strcmp(av[1], "sha256") == 0)
		data->cmd.cmd_flg = 2;
	return (0);
}
