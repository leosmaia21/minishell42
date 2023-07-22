SRCS = main.c lexer.c utils.c signals.c envp.c
NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -lreadline -g
RM = rm -f
OBJS= $(SRCS:.c=.o)
INCS	= libft/libft.a

ifeq ($(shell uname), Linux)
	CFLAGS = -Wall  -Wextra -lreadline
	FSANITIZE = -fsanitize=leak
else ifeq ($(shell uname), Darwin)
	CFLAGS	+= -L/Users/$(shell whoami)/.brew/opt/readline/lib -lreadline
	INCS	+= -I/Users/$(shell whoami)/.brew/opt/readline/include
endif

RUN = ./$(NAME)
ifdef DEBUG
		CFLAGS += -g
		RUN = 
endif

all: ${NAME}

$(NAME):runlibft $(OBJS)
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}
		$(RUN)

ignore:
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}

clean:
	${RM} ${OBJS}

fclean:clean 
	${RM} ${NAME}
	make -C libft fclean

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean
