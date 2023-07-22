SRCS := main.c lexer.c utils.c signals.c
HEADERS := utils.h minishell.h lexer.h
NAME := minishell
CC := clang
CFLAGS := -Wall  -Wextra -lreadline 
RM := rm -f
OBJS:= $(SRCS:.c=.o)
INCS	:= libft/libft.a

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
	${RM} ${OBJS}

fclean:clean 
	${RM} ${NAME}
	# make -C libft fclean

re:fclean all

runlibft:
	make -C libft

.PHONY:all re clean fclean
