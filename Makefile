# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touahman <touahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 13:03:48 by touahman          #+#    #+#              #
#    Updated: 2024/01/09 17:20:08 by touahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCF_C = client.c utils.c
SRCF_S = server.c utils.c

OBJF_C = $(SRCF_C:.c=.o)
OBJF_S = $(SRCF_S:.c=.o)

NAME_C = client

NAME_S = server

all : $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJF_C)
	$(CC) $(CFLAGS) $^ -o $@ 

$(NAME_S): $(OBJF_S)
	$(CC) $(CFLAGS) $^ -o $@ 

$(OBJF_C) : header.h
$(OBJF_S) : header.h

clean:
	rm -f $(OBJF_C) $(OBJF_S)

fclean: clean
	rm -f $(NAME_C) $(NAME_S)

re: fclean all

.PHONY : all clean fclean re
