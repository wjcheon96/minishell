# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 22:01:20 by eunrlee           #+#    #+#              #
#    Updated: 2023/02/02 22:28:59 by wocheon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra
RL_LIB = -lreadline -L$(HOME)/.brew/opt/readline/lib
RL_INC = -I$(HOME)/.brew/opt/readline/include
NAME = minishell
LIBFT = ./libft/libft.a
SRCS = ./srcs/main.c ./srcs/env_ctl.c ./srcs/environ.c ./srcs/arr.c ./srcs/excute.c \
	./srcs/redirection.c ./srcs/ft_cmd.c ./srcs/builtins.c ./srcs/dir.c \
	./srcs/free.c ./srcs/heredoc.c ./srcs/error.c ./srcs/check_str.c ./srcs/signal.c \
	./srcs/parse.c ./srcs/list.c ./srcs/check.c ./srcs/seperate_quote.c ./srcs/dollar.c \
	./srcs/seperate_type.c ./srcs/seperate_space.c ./srcs/heredoc_utils.c
OBJS = $(SRCS:.c=.o)
HEADER = -I./includes

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(HEADER) $(LIBFT) $(OBJS) $(RL_LIB)
%.o : %.c
			$(CC) $(CFLAGS) $(RL_INC) $(HEADER) -c $< -o $@
$(LIBFT) :
		make -C ./libft bonus
clean :
		make -C ./libft fclean
		rm -rf $(OBJS)
fclean : clean
		rm -rf $(NAME)
re :
		make fclean
		make all
		
