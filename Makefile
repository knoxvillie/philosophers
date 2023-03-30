# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:41:23 by kfaustin          #+#    #+#              #
#    Updated: 2023/03/28 12:38:02 by kfaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# - 	BINARY 		//////
NAME	= philo

# - 	Cc & Flags	//////
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
THREAD	= -pthread

# - 	Src 		//////
SRCDIR	= ./src/
SRC		= action.c checker.c general.c general2.c initialize.c main.c
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJ		= $(addprefix $(SRCDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(THREAD) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all


