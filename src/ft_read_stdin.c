/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:04:39 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/11 02:44:13 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./ft_ssl_md5.h"

int	ft_is_empty_stdin(char *str, int rd)
{
	if (rd == 1 && str[0] == '\n')
		return (1);
	return (0);
}

static int	ft_concat_data(t_data *data, int rd, char *temp, int *malloc_err)
{
	size_t	size;
	char	*buff;

	size = ft_strlen(data->args[0].str) + rd + 1;
	buff = malloc(size);
	if (buff == NULL)
	{
		ft_putstr_std("ft_ssl: error, malloc fail\n", 2);
		*malloc_err = 1;
		free(data->args[0].str);
		free(data->args);
		return (0);
	}
	ft_strcpy(buff, data->args[0].str);
	ft_strcat(buff, temp);
	free(data->args[0].str);
	data->args[0].str = buff;
	return (0);
}

int	ft_handle_read_loop(t_data *data, int rd, char *temp, int *malloc_err)
{
	if (data->n_args == 0)
		return (ft_allocate_for_stdin_arg(data, rd, temp, malloc_err));
	return (ft_concat_data(data, rd, temp, malloc_err));
}

int	ft_read_stdin(t_data *data)
{
	char	temp[100];
	int		rd;
	int		ret;
	int		malloc_err;

	malloc_err = 0;
	rd = read(0, temp, 99);
	if (rd <= 0)
		rd = 0;
	else
		temp[rd] = '\0';
	if (rd == 1 && temp[0] == '\n')
		ret = ft_handle_read_loop(data, 1, "\n", &malloc_err);
	else
		ret = ft_handle_read_loop(data, rd, temp, &malloc_err);
	if (malloc_err == 1 || ret)
		return (1);
	return (0);
}
