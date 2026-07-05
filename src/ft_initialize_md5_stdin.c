/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_md5_stdin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 01:29:30 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/26 01:55:02 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

static void    ft_copy_data_to_blocks_stdin(t_hash_md5 *md5, t_data *data)
{
        size_t pos;
        char *str;

        str = data->args[0].str;
        pos = 0;
        md5->i = 0;
        md5->j = 0;
        while (str[md5->i])
        {
                md5->blocks[md5->j][pos++] = str[md5->i];
                if (pos == 64)
                {
                        md5->j++;
                        pos = 0;
                }
                md5->i++;
        }
        if (pos == 64)
        {
                md5->j++;
                pos = 0;
        }
        md5->blocks[md5->j][pos++] = 0x80;
        while (pos < 64)
                md5->blocks[md5->j][pos++] = 0x00;
}


int ft_initialize_md5_stdin(t_hash_md5 *md5, t_data *data)
{
        md5->str_len = ft_strlen(data->args[0].str);
        md5->bit_len = md5->str_len * 8;
        md5->blks_len = (md5->str_len + 9) / 64 + 1;
        if (ft_allocate_block_memory(md5))
            return (1);
        ft_copy_data_to_blocks_stdin(md5, data);
        ft_add_size_to_block(md5);
        md5->a = A_CONS;
        md5->b = B_CONS;
        md5->c = C_CONS;
        md5->d = D_CONS;
        ft_init_k(md5->k);
        ft_init_s(md5->s);
        return (0);
}

