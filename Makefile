SRCS = main.c lexer.c utils.c signals.c
NAME = minishell
CC = clang
FLAGS = -Wall -g -Werror -Wextra -lreadline #-fsanitize=thread
RM = rm -f
OBJS= $(SRCS:.c=.o)
INCS	= libft/libft.a

all: ${NAME}

$(NAME):runlibft $(OBJS)
		${CC} ${FLAGS} -o ${NAME} ${OBJS} ${INCS}

ignore:
	${CC} ${FLAGS} -o ${NAME} ${OBJS} ${INCS}

clean:
	${RM} ${OBJS}

fclean:clean 
	${RM} ${NAME}
	make -C libft fclean

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean
