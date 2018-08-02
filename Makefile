# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/18 12:13:38 by nithramir         #+#    #+#              #
#    Updated: 2018/08/02 18:16:38 by nithramir        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRC_PATH = ft_ping_src

OBJ_PATH = ft_ping_obj

H_FILES= ft_ping.h

SRC = main.o\

CC = gcc -g -I. -fsanitize=address

FLAG = -Wall -Wextra -O # -Werror

LIB = libft/libftprintf.a libft_chained_list/libft_chained_list.a

SRC_O = $(addprefix $(OBJ_PATH)/,$(SRC))


all: EXEC $(NAME)

$(NAME): $(SRC_O)
	$(CC) $(FLAG) -o $(NAME) $(SRC_O) $(LIB)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

EXEC:
	make -C libft/
	make -C libft_chained_list/

clean:
	rm -f $(addprefix $(OBJ_PATH)/,$(SRC))
	make -C libft clean
	make -C libft_chained_list clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C libft_chained_list fclean


re: fclean all

flag: $(SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all

.PHONY: $(NAME) all %.o clean fclean re flag EXEC