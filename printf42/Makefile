# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 15:30:17 by roalexan          #+#    #+#              #
#    Updated: 2024/11/23 15:32:51 by roalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 		ft_print_char.c\
					ft_print_nbr.c\
					ft_print_str.c\
					ft_print_hex.c\
					ft_print_upperhex.c\
					ft_print_unbr.c\
					ft_print_pointer.c\
					ft_printf.c\

OBJS = $(SRCS:%.c=%.o)

NAME	= libftprintf.a

CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)
clean:
				$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY : all clean fclean re