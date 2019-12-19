# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/16 11:10:57 by akhossan          #+#    #+#              #
#    Updated: 2019/12/16 13:26:21 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	akhossan.filler

CFLAGS	=	-Werror -Wextra -Wall

FILES	=	main.c\
			map.c\
			piece.c\
			player.c\
			scores.c\
			solve.c\
			utils.c\
			heat_map.c\
			coordinates.c	

SRCDIR	=	srcs

OBJDIR	=	objs

SRCS	=	$(addprefix $(SRCDIR)/,$(FILES))

OBJS	=	$(addprefix $(OBJDIR)/, $(FILES:.c=.o))

LIBSDIR	=	libs/ft_printf

FT_PRINTF=	$(LIBSDIR)/libftprintf.a

INC		=	-I $(LIBSDIR)/inc -I includes

LIBS	=	-lftprintf -L $(LIBSDIR)

HEADERS	=	includes/filler.h


all : $(NAME)

$(OBJDIR):
	@mkdir -p $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	gcc -c $(CFLAGS) $(INC) $< -o $@

$(FT_PRINTF):
	@make -C $(LIBSDIR)

$(NAME) : $(OBJDIR) $(FT_PRINTF) $(OBJS)
	@gcc $(CFLAGS) $(OBJS) $(LIBS) $(INC) -o $@
	@echo "\033[44m\033[93m\033[21mfiller...[OK]\033[49m\033[93m"

clean :
	make clean -C $(LIBSDIR)
	/bin/rm -rf $(OBJDIR)

fclean : clean
	make fclean -C $(LIBSDIR)
	/bin/rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean all re
