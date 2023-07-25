SRCS = main.c lexer.c utils.c signals.c envp.c execs.c
NAME = minishell
CC = cc
FLAGS = -Wall -g -Werror -Wextra -lreadline #-fsanitize=thread

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
		CFLAGS += -ggdb -O0
		RUN = 
endif
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $<   -c   

all: ${NAME}

$(NAME):runlibft $(OBJS)
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}
		$(RUN)


ignore:
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}

clean:
	${RM} ${OBJdS}

fclean:clean 
	${RM} ${NAME}
	make -C libft fclean

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean
