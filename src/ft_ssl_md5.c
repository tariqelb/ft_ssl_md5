/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:13:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/17 00:19:10 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

void	ft_initialize_data(t_data *data, int ac, char **av)
{
	data->op.r = 0;
	data->op.q = 0;
	data->op.p = 0;
	data->n_args = 0;
	data->str_muted = -1;
	data->s_flag_on = 0;
	data->cmd.cmd_flg = 0;
	data->args = NULL;
	data->av = av;
	data->ac = ac;
	ft_strcpy(data->cmd.md5, "md5");
	ft_strcpy(data->cmd.sha256, "sha256");
}

void	ft_display_struct(t_data *data)
{
	printf("\n-----------------------------------------\n\n");
	printf("flags : -q %d -r %d -p %d\n", data->op.q, data->op.r, data->op.p);
	printf("nbr of args %d, is str muted : %d\n", data->n_args, data->str_muted);	
	if (data->op.p && data->args)
		printf("std in : {%s}\n", data->args->str);
	printf("command is : %d\n", data->cmd.cmd_flg);
	printf("\n-----------------------------------------\n\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_initialize_data(&data, ac, av);
	printf("------------------------------------------\n");
	if (ft_parse_command_errors(ac, av, &data))
		return (1);
	printf("------------------------------------------\n");
	if (ft_parse_and_get_option(ac, av, &data))
		return (1);
	printf("------------------------------------------\n");
	if (data.op.p && ft_read_stdin(&data))
		return (0);
	printf("------------------------------------------\n");
	ft_execute_args(&data);
	ft_display_struct(&data);
	return (0);
}
