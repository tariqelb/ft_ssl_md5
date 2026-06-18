/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file_prefix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 02:35:49 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/18 02:37:45 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int     ft_display_file_prefix(int i, t_data *data) 
{ 
        if (data->op.r == 0) 
        { 
                if (data->cmd.cmd_flg == 1) 
                        ft_putstr_std("MD5 ", 1); 
                else 
                        ft_putstr_std("SHA256 ", 1); 
                ft_putstr_std("(", 1); 
                ft_putstr_std(data->av[i], 1); 
                ft_putstr_std(") = \n", 1); 
        } 
        else 
        { 
                ft_putstr_std("", 1); 
                ft_putstr_std(data->av[i], 1); 
                ft_putstr_std("\n", 1); 
        }                
        return (0); 
}
