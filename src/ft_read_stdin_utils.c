/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:39:03 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 02:39:41 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_init_stdin_arg(t_data *data, int rd, int *malloc_err)
{
	data->args = malloc(sizeof(t_args) * 2);
	if (data->args == NULL)
	{
		ft_putstr_std("ft_ssl: error, malloc fail\n", 2);
		*malloc_err = 1;
		return (0);
	}
	data->args[0].type = 0;
	data->args[0].str = malloc(rd + 1);
	if (data->args[0].str == NULL)
	{
		ft_putstr_std("ft_ssl: error, malloc fail\n", 2);
		*malloc_err = 1;
		free(data->args);
		return (0);
	}
	return (1);
}

int	ft_fill_stdin_arg(t_data *data, int rd, char *temp)
{
	if (rd == 0)
		data->args[0].str[0] = '\0';
	else if (ft_is_empty_stdin(temp, rd))
	{
		if (rd == 1)
		{
			data->args[0].str[0] = '\n';
			data->args[0].str[1] = '\0';
		}
		else
			data->args[0].str[0] = '\0';
	}
	else
		ft_strcpy(data->args[0].str, temp);
	data->n_args++;
	return (0);
}

int	ft_allocate_for_stdin_arg(t_data *data, int rd, char *temp,
		int *malloc_err)
{
	if (!ft_init_stdin_arg(data, rd, malloc_err))
		return (0);
	return (ft_fill_stdin_arg(data, rd, temp));
}
