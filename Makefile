SRCS = main.c main2.c lexer.c lexer2.c lexer3.c lexer4.c utils.c signals.c envp.c envp2.c envp3.c execs.c execs2.c execs3.c builtins.c builtins2.c cd.c free.c redirect.c heredoc.c
NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -O3 -g -fsanitize=address

RM = rm -f
OBJS = $(SRCS:.c=.o)
INCS = libft/libft.a


RUN = ./$(NAME)
all: ${NAME}

$(NAME):runlibft $(OBJS)
		${CC} ${CFLAGS} -lreadline -o  ${NAME} ${OBJS} ${INCS}

deb:runlibft $(OBJS)
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}

ignore:
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}

clean:
	${RM} ${OBJS}

fclean:clean 
	# make fclean -C libft
	${RM} ${NAME}

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean

.SILENT: