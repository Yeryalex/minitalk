# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 12:07:16 by yrodrigu          #+#    #+#              #
#    Updated: 2024/07/30 20:42:37 by yrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES =	client.c\
			ft_utilities.c\
			server.c\

BONUS_CFILES= client_bonus.c\
			  ft_utilities.c\
			  server_bonus.c\

OFILES = $(CFILES:.c=.o)
BONUS_OFILES = $(BONUS_CFILES:.c=.o)

CLIENT_OFILES = client.o ft_utilities.o
SERVER_OFILES = server.o ft_utilities.o

BONUS_CLIENT_OFILES = client_bonus.o ft_utilities.o
BONUS_SERVER_OFILES = server_bonus.o ft_utilities.o


all: client server

bonus: client_bonus server_bonus

client: $(OFILES)
		$(CC) $(CFLAGS) $(CLIENT_OFILES) -o client

server: $(OFILES)
		$(CC) $(CFLAGS) $(SERVER_OFILES) -o server

client_bonus: $(BONUS_CLIENT_OFILES)
		$(CC) $(CFLAGS) $(BONUS_CLIENT_OFILES) -o client_bonus

server_bonus: $(BONUS_SERVER_OFILES)
		$(CC) $(CFLAGS) $(BONUS_SERVER_OFILES) -o server_bonus

%.o: %.c libft.h 
		$(CC) $(CFLAGS) -c $<

%bonus.o: %bonus.c  libft.h
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f $(OFILES) $(BONUS_OFILES)

fclean: clean
		rm -f client server client_bonus server_bonus

re: fclean all

.PHONY: all bonus clean fclean re
