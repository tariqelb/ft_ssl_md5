/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:04:39 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/09 21:02:09 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./ft_ssl_md5.h"

static int	ft_is_empty_stdin(char *str, int rd)
{
	if (rd == 1 && str[0] == '\n')
		return (1);
	return (0);
}

static int	ft_allocate_for_stdin_arg(t_data *data,
			int rd, char *temp, int *malloc_err)
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
	if (ft_is_empty_stdin(temp, rd))
		data->args[0].str[0] = '\0';
	else
		ft_strcpy(data->args[0].str, temp);
	data->n_args++;
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

static int	ft_handle_read_loop(t_data *data,
			int rd, char *temp, int *malloc_err)
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
	if (rd == -1)
		return (0);
	while (rd > 0)
	{
		temp[rd] = '\0';
		ret = ft_handle_read_loop(data, rd, temp, &malloc_err);
		if (malloc_err == 1 || ret)
			return (1);
		rd = read(0, temp, 99);
	}
	if (data->n_args == 0)
	{
		ret = ft_handle_read_loop(data, 0, "", &malloc_err);
		if (malloc_err == 1 || ret)
			return (1);
	}
	return (0);
}
/*
int	ft_read_stdin(t_data *data)
{
	char	temp[100];
	int		rd;
	int		ret;
	int		malloc_err;

	malloc_err = 0;
	ft_bzero(temp, 100);
	rd = read(0, temp, 99);
	if (rd == -1)
		return (0);
	while (rd > 0)
	{
		temp[rd] = '\0';
		ret = ft_handle_read_loop(data, rd, temp, &malloc_err);
		if (malloc_err == 1 || ret)
			return (1);
		if (ft_is_empty_stdin(temp, rd))
			return (0);
		rd = read(0, temp, 99);
	}
	return (0);
}
*/
