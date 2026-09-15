# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/12 22:54:33 by tel-bouh          #+#    #+#              #
#    Updated: 2026/09/15 15:12:18 by tariq            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ssl

SRCS=	./ft_parse_command_errors.c \
	./ft_printf_utils.c \
	./ft_utils_one.c \
	./ft_utils_two.c \
	./ft_read_stdin.c \
	./ft_read_stdin_utils.c \
	./ft_parse_and_get_option.c \
	./ft_execute_args.c \
	./ft_fg_round.c \
	./ft_free_md5.c \
	./ft_display_prefix.c \
	./ft_option_str_flag.c \
	./ft_enrypt_string.c \
	./ft_enrypt_file.c \
	./ft_display_str_prefix.c \
	./ft_display_file_prefix.c \
	./ft_initialize_md5.c \
	./ft_process_blocks.c \
	./ft_printf_md5.c \
	./ft_init_s_and_k.c \
	./ft_initialize_md5_stdin.c \
	./ft_initialize_md5_file.c \
	./ft_allocate_block_memory_sha.c \
	./ft_initialize_sha256_stdin.c \
	./ft_display_hash_sha256.c \
	./ft_initialize_sha256_file.c \
	./ft_initialize_sha_string.c \
	./ft_init_k_sha256.c \
	./ft_build_message_shedule.c \
	./ft_process_blocks_sha256.c \
	./ft_print_sha256.c \
	./ft_sha256_process_one.c \
	./ft_sha256_process_two.c \
	./ft_ssl_md5.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) #clean

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -I . $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
