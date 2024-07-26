# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 12:07:16 by yrodrigu          #+#    #+#              #
#    Updated: 2024/07/26 12:53:09 by yrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES =	client.c\
			ft_utilities.c\
			server.c\

OFILES = $(CFILES:.c=.o)

CLIENT_OFILES = client.o ft_utilities.o
SERVER_OFILES = server.o ft_utilities.o

all: client server

client: $(OFILES)
		$(CC) $(CFLAGS) $(CLIENT_OFILES) -o client

server: $(OFILES)
	$(CC) $(CFLAGS) $(SERVER_OFILES) -o server

%.o: %.c libft.h 
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f $(OFILES)

fclean: clean
		rm -f client server

re: fclean all

.PHONY: all clean fclean re
