# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/12 22:54:33 by tel-bouh          #+#    #+#              #
#    Updated: 2026/06/20 23:24:29 by tel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ssl

SRCS=	./ft_parse_command_errors.c \
	./ft_printf_utils.c \
	./ft_utils_one.c \
	./ft_utils_two.c \
	./ft_read_stdin.c \
	./ft_parse_and_get_option.c \
	./ft_execute_args.c \
	./ft_display_prefix.c \
	./ft_option_str_flag.c \
	./ft_enrypt_string.c \
	./ft_enrypt_file.c \
	./ft_display_str_prefix.c \
	./ft_display_file_prefix.c \
	./ft_ssl_md5.c

FLAGS= -Werror -Wextra -Wall

all:
	gcc $(FLAGS) -o ${NAME} ${SRCS}

fclean:
	/bin/rm -rf ${NAME}
