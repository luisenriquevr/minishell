# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 20:13:17 by cmarcu            #+#    #+#              #
#    Updated: 2022/03/07 21:23:43 by lvarela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSPATH	= ./srcs/
SRCS = readlinepruebas.c fill_cmd_line.c list_cmd_line.c tokenizer.c \
		checking.c update_tokens.c printtitle.c error_functions.c \
		

SRC = $(addprefix $(SRCSPATH), $(SRCS))

OBJS = $(SRC:.c=.o)

NAME = minishell

CC = gcc
CFLAGS = -Werror -Wextra -Wall $(INCLUDES) -g3 -fsanitize=address
LDFLAGS = -L$(LIBFTPATH) -lft -lreadline -g3 -fsanitize=address
RM = rm -f

SRCINC = include/

INCLUDES = -I$(SRCINC) -I$(LIBFTPATH)

LIBFTPATH	= ./libft/
LIBFTNAME =	libft.a
LIBFT =	$(LIBFTPATH)$(LIBFTNAME)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTPATH)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
