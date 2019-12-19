# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 14:36:13 by akhossan          #+#    #+#              #
#    Updated: 2019/11/29 17:59:25 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Werror -Wextra -Wall

SRCS = $(shell find . -type f -name "*.c")

OBJS = $(SRCS:.c=.o)

HEADER = libft.h

all : $(NAME)

%.o: %.c $(HEADER)
	@printf "\033[32m\033[1m"
	gcc $(CFLAGS)   -c $< -o $@

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[44m\033[93m\033[21mLibft...[OK]\033[49m\033[93m"

clean :
	@/bin/rm -f $(OBJS)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
