# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 20:13:17 by cmarcu            #+#    #+#              #
#    Updated: 2022/02/23 20:24:32 by cmarcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSPATH	= ./srcs/
SRCS = readlinepruebas.c

SRC = $(addprefix $(SRCSPATH), $(SRCS))

OBJS = $(SRC:.c=.o)

NAME = minishell

CC = gcc
CFLAGS = -Werror -Wextra -Wall $(INCLUDES)#-g3 -fsanitize=address
LDFLAGS = -L$(LIBFTPATH) -lft
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
