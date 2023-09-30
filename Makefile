SRCS = main.c lexer.c utils.c signals.c envp.c envp2.c envp3.c execs.c execs2.c builtins.c builtins2.c cd.c free.c redirect.c heredoc.c
NAME = minishell
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = rm -f
OBJS = $(SRCS:.c=.o)
INCS = libft/libft.a

# ifeq ($(shell uname), Linux)
# 	CFLAGS = -glldb -Wall  -Wextra -lreadline
# 	FSANITIZE = -fsanitize=leak
# else ifeq ($(shell uname), Darwin)
# 	CFLAGS	+= -L/Users/$(shell whoami)/.brew/opt/readline/lib -lreadline
# 	INCS	+= -I/Users/$(shell whoami)/.brew/opt/readline/include
# endif

RUN = ./$(NAME)
all: ${NAME}

$(NAME):runlibft $(OBJS)
		${CC} ${CFLAGS} -lreadline -o  ${NAME} ${OBJS} ${INCS}
#		$(RUN)

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
