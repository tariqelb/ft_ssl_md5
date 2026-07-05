/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:37:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/27 02:10:09 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_end_with_newline(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (str[size - 1] == '\n')
		return (size);
	else
		return (0);
}


void	ft_prefix_p_q(t_data *data)
{
	int	size;

	if (data->op.p == 0 && data->op.q)
		return ;
	if (data->op.p == 0 && data->op.q == 0)
		ft_putstr_std("(stdin)= ", 1);	
	else if (data->op.p && data->op.q)
	{
		ft_putstr_std(data->args[0].str, 1);
		//ft_putstr_std("\n", 1);
	}
	else if (data->op.p)
	{
		ft_putstr_std("(\"", 1);
		size = ft_end_with_newline(data->args[0].str);
		if (size)
		{
			data->i = 0;
			while (data->i < size - 1 && data->args[0].str[data->i])
			{
				write(1, &data->args[0].str[data->i], 1);	
				data->i++;
			}
		}
		else
			ft_putstr_std(data->args[0].str, 1);
		ft_putstr_std("\")= ", 1);
	}
}

int	ft_display_prefix(t_data *data)
{
	//print stdin
	if (data->n_args && data->args && data->args[0].type == 0)
		ft_prefix_p_q(data);
	return (0);
}
