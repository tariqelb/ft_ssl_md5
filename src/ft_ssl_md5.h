/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:10:06 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/18 02:57:16 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

//# define RANDOM 1 //global
# define RANDOM 0 //before file

typedef struct s_opt
{
	short	r;
	short	q;
	short	p;
}		t_opt;

typedef struct s_cmd
{
	short	cmd_flg;
	char	md5[4];
	char	sha256[7];
}		t_cmd;

typedef struct s_args
{
	short	type; //0=stdin,1=file,2=string
	char	*str;
	int	fd;
	char	*filename;
	char	*hash;
	char	*prefix_str;
}		t_args;


typedef struct s_data
{
	t_opt	op;
	t_cmd	cmd;
	t_args	*args;
	int	i;
	int	j;
	int	ac;
	char	**av;
	int	n_args;
	short	s_flag_on;
	short	str_muted;
}		t_data;


//File : ft_printf_utils.c
int	ft_putstr_std(char *str, int std);
int	ft_puthex(unsigned int nbr, int flag, int std);
int	ft_put_size_t(size_t nbr, int std);
int	ft_putint(int nbr, int std);

//File : ft_utils_one.c
char	*ft_strcat(char *dest, const char *src);
void	ft_put_str(char *str);
void	ft_bzero(void *s, size_t n);


//File : ft_utils_two.c
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*ft_strcpy(char *dest, const char *src);
void	*ft_memcpy(void *dest, void *src, size_t n);
int	ft_strcmp(char *s1, char *s2);

//File : main.c
void	ft_initialize_data(t_data *data, int ac, char **av);

//File : ft_parse_commad_errors.c
int     ft_parse_command_errors(int ac, char **av, t_data *data);

//File : ft_read_stdin.c
int     ft_read_stdin(t_data *data);

//File : ft_parse_and_get_option.c
int     ft_parse_and_get_option(int ac, char **av, t_data *data);

//File : ft_display_prefix.c
void    ft_prefix_p_q(t_data *data);
int     ft_display_prefix(t_data *data);

//File : ft_execute_args.c
void    ft_display_hash(t_data *data);
int     ft_execute_args(t_data *data);

//File : ft_encrypt_string.c
int     ft_display_string_error(t_data *data, int i);
int     ft_check_isit_followed_by_string(t_data *data, int i);
int     ft_encript_string(int i, t_data *data);

//File : ft_encrypt_file.c
int     ft_display_file_error(t_data *data, int i);
int     ft_encript_file(int i, t_data *data);

//File : ft_option_string_flag.c
int     ft_is_one_global_option(int i, t_data *data);
int     ft_check_is_string_flag(int i, t_data *data);

//File : ft_display_str_prefix.c
int     ft_display_str_prefix(int i, t_data *data);
//File : ft_display_file_prefix.c
int     ft_display_file_prefix(int i, t_data *data);

#endif
