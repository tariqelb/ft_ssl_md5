/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:04:39 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/20 19:48:31 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static int	ft_exit(char *str, t_data *data)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	if (ft_strcmp(&str[i], "\n") == 0)
	{
		data->args[0].str[i] = 0;
		return (1);
	}
	return (0);
}

static int     ft_allocate_for_stdin_arg(t_data *data, int rd, char *temp, int *malloc_err)
{
	data->args = NULL;
	data->args = malloc(sizeof(t_args) * 2);
	if (data->args == NULL)
	{
		ft_putstr_std("ft_ssl: error, malloc fail\n", 2);
		*malloc_err = 1;
		return (0);
	}
	data->args[0].type = 0;
	data->args[0].str = NULL;
	data->args[0].str = malloc(rd + 1);
	if (data->args[0].str == NULL)
	{
		ft_putstr_std("ft_ssl: error, malloc fail\n", 2);
		*malloc_err = 1;
		free(data->args);
		return (0);
	}
	ft_strcpy(data->args[0].str, temp);
	data->n_args++;
	if (ft_exit(temp, data))
		return (1);
	return (0);
}

static int     ft_concat_data(t_data *data, int rd, char *temp, int *malloc_err)
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
	if (ft_exit(buff, data))
		return (1);
	return (0);
}

static int	ft_handle_read_loop(t_data *data, int rd, char *temp, int *malloc_err)
{
	if (data->n_args == 0)
	{
		return (ft_allocate_for_stdin_arg(data, rd, temp, malloc_err));
	}
	else 
	{
		return (ft_concat_data(data, rd, temp, malloc_err));
	}
	return (0);
}

int     ft_read_stdin(t_data *data)
{
	printf("ft_read_stdin\n");
	int     rd;
	int     ret;
	int     i;
	char    temp[100];
	int     malloc_err;

	malloc_err = 0;
	ft_bzero(temp, 100);
	rd = read(0 , temp, 99);
	if (rd == -1 || rd == 0)
		return (0);
	i = 0;
	while (rd)
	{
		temp[rd] = '\0';
		ret = ft_handle_read_loop(data, rd, temp, &malloc_err);
		if (malloc_err == 1)
			return (1);
		if (ret)
			return (0);
		rd = read(0 , temp, 99);
		i++;
	}
	return (0);
}
