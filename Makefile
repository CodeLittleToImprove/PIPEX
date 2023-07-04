# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:08:12 by tbui-quo          #+#    #+#              #
#    Updated: 2023/05/31 15:02:08 by tbui-quo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= pipex
				
LIBFT			= libft

SRCDIR			= srcs

SRCS			= main.c pipex.c error.c utils.c

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

OBJS			= ${SRCS:.c=.o}

HEADER			= pipex.h

RM				= rm -f

all:			lib ${NAME}

${NAME}:		${OBJS} ${LIBFT}/libft.a
				${CC} ${CFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}

${OBJS}:		${HEADER}

lib:
				make -C ${LIBFT} 

clean:	
				${RM} ${OBJS}
				make clean -C ${LIBFT}

fclean:			clean
				${RM} ${NAME}
				make fclean -C ${LIBFT}

re:				fclean all