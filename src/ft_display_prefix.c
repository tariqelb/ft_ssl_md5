/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:37:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/20 20:14:31 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_display_prefix_rev(t_data *data);

void	ft_prefix_p_q(t_data *data)
{
	if (data->op.p == 0 && data->op.q)
		return ;
	if (data->op.p == 0 && data->op.q == 0)
		ft_putstr_std("(stdin)= ", 1);	
	else if (data->op.p && data->op.q)
	{
		ft_putstr_std(data->args[0].str, 1);
		ft_putstr_std("\n", 1);
	}
	else if (data->op.p)
	{
		ft_putstr_std("(\"", 1);
		if (data->n_args)
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
