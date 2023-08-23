# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 13:48:18 by cafraixe          #+#    #+#              #
#    Updated: 2023/08/23 16:56:40 by cafraixe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= philo

HEADER_FILE			= philosophers.h

SRCS		         =	main.c \
						parse_n_init.c \
						routine.c \
						utils.c \
						norme.c \

OBJS				= ${SRCS:.c=.o}

CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread #-g3 -fsanitize=address
RM					= rm -f

OBJ 				= $(OBJS)
HEADER 				= $(HEADER_FILE)

$(NAME):	${OBJ}
			$(CC) $(CFLAGS) ${OBJ} -o $(NAME)

all:		${NAME}

%.o: %.c	$(HEADER)
			$(CC) -c $(CFLAGS) -o $@ $<

re: 		fclean all

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

.PHONY: 	all clean fclean re