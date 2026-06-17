/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_get_option.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:06:17 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/16 23:56:00 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static void     ft_is_an_option(char *av, t_data *data)
{
	printf("ft_is_an_option \n");
        if (ft_strcmp(av, "-r") == 0)
                data->op.r = 1;
        else if (ft_strcmp(av, "-q") == 0)
                data->op.q = 1;
        else if (ft_strcmp(av, "-p") == 0)
                data->op.p = 1;
        return ;
}

int	ft_parse_and_get_option(int ac, char **av, t_data *data)
{
	printf("ft_parse_and_get_option\n");
	int	i;
	int	fd;

	i = 2;
	while (i < ac)
	{
		fd = 0;
		if (data->str_muted == -1)
			fd = open(av[i], O_RDONLY);
		if (fd > 2)
		{
			close(fd);
			data->str_muted = i;
			printf("file found %s %d\n", av[i], data->str_muted);
		}
		//printf("parse opt : %d %d %s\n", i, data->str_muted, av[i]);
		if (RANDOM)
			ft_is_an_option(av[i], data);
		else if (data->str_muted == -1)
			ft_is_an_option(av[i], data);
		i++;	
	}
	return (0);
}
