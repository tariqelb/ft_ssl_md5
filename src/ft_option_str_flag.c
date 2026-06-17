/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option_str_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:43:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/17 04:44:24 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int     ft_is_one_global_option(int i, t_data *data)
{
        if (ft_strcmp(data->av[i], "-r") == 0)
                return (1);
        if (ft_strcmp(data->av[i], "-p") == 0)
                return (1);
        if (ft_strcmp(data->av[i], "-q") == 0)
                return (1);
        return (0);
}

int     ft_check_is_string_flag(int i, t_data *data)
{
        if (ft_strcmp(data->av[i], "-s") == 0)
        {
                data->s_flag_on = i;
                return (1);
        }       
        return (0);
}
