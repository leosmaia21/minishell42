# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 22:56:00 by bde-sous          #+#    #+#              #
#    Updated: 2023/04/10 11:09:26 by bde-sous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isascii.c	ft_memcpy.c		ft_putstr_fd.c	ft_strncmp.c	\
					ft_atoi.c		ft_isdigit.c	ft_memmove.c	ft_strchr.c		\
					ft_strnstr.c 	ft_bzero.c		ft_isprint.c	ft_memset.c		\
					ft_strdup.c		ft_strrchr.c 	ft_calloc.c		ft_putchar_fd.c	\
					ft_strjoin.c	ft_substr.c 	ft_isalnum.c	ft_memchr.c		\
					ft_strlcat.c	ft_tolower.c 	ft_striteri.c	ft_memcmp.c		\
					ft_putendl_fd.c	ft_strlcpy.c	ft_toupper.c 	ft_isalpha.c	\
					ft_putnbr_fd.c	ft_strlen.c 	ft_strtrim.c 	\
					ft_split.c 		ft_itoa.c		ft_strmapi.c	

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c \
					ft_lstdelone.c	ft_lstclear.c		ft_lstiter.c	ft_lstmap.c

BONUS_OBJS		= $(BONUS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libft.a


all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)


bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus