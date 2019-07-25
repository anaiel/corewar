# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 09:14:19 by dtrigalo          #+#    #+#              #
#    Updated: 2019/07/05 10:49:56 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra

SRCSFD = srcs/
SRC = ft_printf.c	\
	  parse_conv.c \
	  conv_functions_char.c \
	  conv_functions_int.c \
	  conv_functions_double.c \
	  conv_functions_percentage.c	\
	  conv_functions_binary.c	\
	  parse_accufield.c \
	  accufield_functions.c \
	  parse_flag.c \
	  flag_functions.c \
	  color_functions.c \
	  exit_error.c \
	  print_current.c \
	  write_arg.c \
	  converter.c \
	  add_flag.c \
	  tools.c
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD), $(SRC:.c=.o))

HDRSFD = includes/
HDR = ft_printf.h
HRDS = $(addprefix $(HRDSFD), $(HRD))

HDR_INC = -I./includes
LIBFT_HDR = -I./libft/inc
LIB_BINARY = -L./libft -lft
LIBFT = libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: check_libft project $(HDRS) $(NAME)

$(NAME): $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@ar rc $(NAME) $(OBJS) libft/obj/*.o
	@ranlib $(NAME)
	@echo "[ $(GREEN)✔$(NONE) ] $@ library"

check_libft:
	@echo "Checking libft..."
	@make -C libft

project:
	@echo "Checking libftprintf"

$(OBJSFD):
	@mkdir $@
	@echo "[ $(GREEN)✔$(NONE) ] $(OBJSFD) directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS) $(LIBFT)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "[ $(RED)✗$(NONE) ] $(NAME) library"
	@make -C ./libft fclean

re: fclean all

.PHONY: check_libft project all clean fclean re
