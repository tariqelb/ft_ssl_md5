/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:10:06 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/09/15 19:06:24 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <math.h>

# define RANDOM 1
# define A_CONS 0x67452301
# define B_CONS 0xefcdab89
# define C_CONS 0x98badcfe
# define D_CONS 0x10325476

# define A_CONST 1779033703
# define B_CONST 3144134277
# define C_CONST 1013904242
# define D_CONST 2773480762
# define E_CONST 1359893119
# define F_CONST 2600822924
# define G_CONST 528734635
# define H_CONST 1541459225

typedef struct s_opt
{
	short	r;
	short	q;
	short	p;
	short	s;
}			t_opt;

typedef struct s_cmd
{
	short	cmd_flg;
	char	md5[4];
	char	sha256[7];
}			t_cmd;

typedef struct s_args
{
	short	type;
	char	*str;
	int		fd;
	char	*filename;
	char	*hash;
	char	*prefix_str;
}			t_args;

typedef struct s_data	t_data;

typedef void			(*t_hash_fun_std)(t_data *data);
typedef void			(*t_hash_fun_str)(int flag, int i, t_data *data);
typedef void			(*t_hash_fun_file)(int flag, int i, t_data *data);

typedef struct s_data
{
	t_opt			op;
	t_cmd			cmd;
	t_args			*args;
	int				i;
	int				j;
	int				ac;
	char			**av;
	int				n_args;
	short			s_flag_on;
	short			str_muted;
	t_hash_fun_std	std[2];
	t_hash_fun_str	str[2];
	t_hash_fun_file	file[2];
}					t_data;

typedef struct s_sha256_blocks
{
	uint32_t	w[64];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	t1;
	uint32_t	t2;
}			t_sha_bkls;

typedef struct s_md5_blocks
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	temp;
	uint32_t	x;
}			t_md5_blocks;

typedef void			(*t_fg_func)(uint32_t *f, uint32_t *g,
				t_md5_blocks *blks, size_t i);

typedef struct s_hash_md5
{
	size_t		i;
	size_t		j;
	size_t		str_len;
	size_t		bit_len;
	size_t		blks_len;
	uint8_t		**blocks;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
	uint32_t	temp;
	uint32_t	x;
	uint32_t	k[64];
	uint32_t	s[64];
	t_fg_func	fg_table[4];
}			t_hash_md5;

typedef struct s_hash_sha256
{
	size_t		i;
	size_t		j;
	size_t		str_len;
	size_t		bit_len;
	size_t		blks_len;
	uint8_t		**blocks;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	k[64];
}			t_hash_sha256;

/* File : ft_printf_utils.c */
int			ft_putstr_std(char *str, int std);
int			ft_puthex(unsigned int nbr, int flag, int std);
int			ft_put_size_t(size_t nbr, int std);
int			ft_putint(int nbr, int std);

/* File : ft_utils_one.c */
char		*ft_strcat(char *dest, const char *src);
void		ft_put_str(char *str);
void		ft_bzero(void *s, size_t n);

/* File : ft_utils_two.c */
size_t		ft_strlen(char *s);
char		*ft_strdup(char *s);
char		*ft_strcpy(char *dest, const char *src);
void		*ft_memcpy(void *dest, void *src, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strncpy(char *dest, const char *src, int size);

/* File : main.c */
void		ft_initialize_data(t_data *data, int ac, char **av);

/* File : ft_parse_commad_errors.c */
int			ft_parse_command_errors(int ac, char **av, t_data *data);

/* File : ft_parse_and_get_option.c */
int			ft_parse_and_get_option(int ac, char **av, t_data *data);

/* File : ft_display_prefix.c */
void		ft_prefix_p_q(t_data *data);
int			ft_display_prefix(t_data *data);

/* File : ft_execute_args.c */
void		ft_display_hash(t_data *data);
int			ft_execute_args(t_data *data);

/* File : ft_encrypt_string.c */
void		ft_hash_str(int newline, int i, t_data *data);
void		ft_hash_str_sha(int newline, int i, t_data *data);
int			ft_display_string_error(t_data *data, int i);
int			ft_check_isit_followed_by_string(t_data *data, int i);
int			ft_encript_string(int i, t_data *data);

/* File : ft_encrypt_file.c */
void		ft_hash_file(int newline, int i, t_data *data);
void		ft_hash_file_sha(int newline, int i, t_data *data);
int			ft_display_file_error(t_data *data, int i);
int			ft_encript_file(int i, t_data *data);

/* File : ft_option_string_flag.c */
int			ft_is_one_global_option(int i, t_data *data);
int			ft_check_is_string_flag(int i, t_data *data);

/* File : ft_display_str_prefix.c */
int			ft_display_str_prefix(int i, t_data *data);

/* File : ft_display_file_prefix.c */
int			ft_display_file_prefix(int i, t_data *data);

/* File : ft_initialize_md5.c */
void		ft_add_size_to_block(t_hash_md5 *md5);
void		ft_copy_data_to_blocks(t_hash_md5 *md5, t_data *data, int idx);
int			ft_allocate_block_memory(t_hash_md5 *md5);
int			ft_initialize_md5_args(t_hash_md5 *md5, t_data *data, int i);

/* File : ft_initialize_md5_file.c */
int			ft_file_len(char *av);
int			ft_copy_data_to_blocks_file(t_hash_md5 *md5, t_data *data, int idx);
int			ft_initialize_md5_file(t_hash_md5 *md5, t_data *data, int i);

/* File : ft_initialize_md5_stdin.c */
int			ft_initialize_md5_stdin(t_hash_md5 *md5, t_data *data);

/* File : ft_process_blocks.c */
int			ft_process_blocks(t_hash_md5 *md5);

/* File : ft_print_md5.c */
void		ft_print_word(uint32_t x);
void		ft_print_md5(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

/* File : ft_init_s_and_k.c */
void		ft_init_s(uint32_t s[64]);
void		ft_init_k(uint32_t k[64]);

/* File : ft_allocate_block_memory_sha.c */
int			ft_allocate_block_memory_sha256(t_hash_sha256 *sha);
void		ft_add_size_to_block_sha256(t_hash_sha256 *sha);

/* File : ft_initialize_sha256_stdin.c */
int			ft_initialize_sha256_stdin(t_data *data, t_hash_sha256 *sha);

/* File : ft_display_hash256.c */
void		ft_display_hash_sha256(t_data *data);

/* File : ft_initialize_sha256_string.c */
int			ft_initialize_sha_string(t_data *data, t_hash_sha256 *sha, int idx);

/* File : ft_initialize_sha256_file.c */
int			ft_copy_data_to_blocks_file_sha(t_hash_sha256 *sha,
				t_data *data, int idx);
int			ft_initialize_sha_file(t_data *data, t_hash_sha256 *sha, int idx);

/* File : ft_init_k_sha256.c */
void		ft_init_k_sha256(uint32_t k[64]);

/* File : ft_build_message_schedule.c */
void		ft_build_w(uint32_t w[64], uint8_t *block);

/* File : ft_process_blocks_sha256.c */
void		ft_process_blocks_sha256(t_hash_sha256 *sha);

/* File : ft_print_sha256.c */
void		ft_print_sha256(t_hash_sha256 *sha);

/* File : ft_fg_round.c */
void		ft_fg_round1(uint32_t *f, uint32_t *g,
				t_md5_blocks *blks, size_t i);
void		ft_fg_round2(uint32_t *f, uint32_t *g,
				t_md5_blocks *blks, size_t i);
void		ft_fg_round3(uint32_t *f, uint32_t *g,
				t_md5_blocks *blks, size_t i);
void		ft_fg_round4(uint32_t *f, uint32_t *g,
				t_md5_blocks *blks, size_t i);
void		ft_init_fg_table(t_hash_md5 *md5);

/* File : ft_free_md5.c */
void		ft_free_md5_i(t_hash_md5 md5, int i);
void		ft_free_md5(t_hash_md5 md5);
void		ft_free_sha256_i(t_hash_sha256 sha, int i);
void		ft_free_sha256(t_hash_sha256 sha);
void		ft_free_data_stdin(t_data data);

/* File : ft_read_stdin.c */
int			ft_handle_read_loop(t_data *data, int rd, char *temp,
				int *malloc_err);
int			ft_read_stdin(t_data *data);

/* File : ft_read_stdin_utils.c */
int			ft_init_stdin_arg(t_data *data, int rd, int *malloc_err);
int			ft_fill_stdin_arg(t_data *data, int rd, char *temp);
int			ft_allocate_for_stdin_arg(t_data *data, int rd, char *temp,
				int *malloc_err);
int			ft_is_empty_stdin(char *str, int rd);

//File: ft_sha256_process_one.c
uint32_t	ft_rotr(uint32_t x, int n);
uint32_t	ft_sigma0(uint32_t x);
uint32_t	ft_sigma1(uint32_t x);
uint32_t	ft_sigma_small0(uint32_t x);
uint32_t	ft_sigma_small1(uint32_t x);

//File: ft_sha256_process_two.c
uint32_t	ft_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t	ft_maj(uint32_t x, uint32_t y, uint32_t z);

#endif
