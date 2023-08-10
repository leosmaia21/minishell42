SRCS = main.c lexer.c utils.c signals.c envp.c execs.c builtins.c free.c
NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread

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
	make fclean -C libft
	${RM} ${NAME}

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean
