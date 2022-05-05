# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 20:13:17 by cmarcu            #+#    #+#              #
#    Updated: 2022/05/05 17:56:42 by lvarela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSPATH = srcs/
SRCS =	main/minishell.c \
		parser/checking.c \
		parser/fill_cmd_line.c \
		parser/list_cmd_line.c \
		parser/tokenizer.c \
		parser/update_tokens.c \
		parser/expander.c \
		parser/prepare_exec.c \
		printtitle.c \
		error_functions.c \
		free_functions.c \
		access_checker.c \
		errors.c \
		exec.c \
		redirection/redirector.c \
		redirection/heredoc.c

BUILTINPATH	= ./srcs/builtins/
BSRCS = builtin_checker.c builtin_cd.c builtin_echo.c builtin_env.c \
	builtin_export.c builtin_pwd.c builtin_unset.c array_utils.c var_utils.c \
	builtin_exit.c

SRC = $(addprefix $(SRCSPATH), $(SRCS)) $(addprefix $(BUILTINPATH), $(BSRCS))

OBJS = $(SRC:.c=.o)

NAME = minishell

RL_INC			= /usr/local/opt/readline/include
RL_LIB			= /usr/local/opt/readline/lib

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
