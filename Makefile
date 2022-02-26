# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 20:13:17 by cmarcu            #+#    #+#              #
#    Updated: 2022/02/26 23:02:45 by cristianama      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSPATH	= ./srcs/
SRCS = readlinepruebas.c fill_cmd_line.c list_cmd_line.c tokenizer.c \
		checking.c

SRC = $(addprefix $(SRCSPATH), $(SRCS))

OBJS = $(SRC:.c=.o)

NAME = minishell

CC = gcc
CFLAGS = -Werror -Wextra -Wall $(INCLUDES)#-g3 -fsanitize=address
LDFLAGS = -L$(LIBFTPATH) -lft -lreadline
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
