NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -lreadline

SRCS = main.c \

OBJS = ${SRCS:.c=.o}

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
			make -s -C libft

$(NAME):	$(LIBFT) $(SRCS)
		$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -o $(NAME)
		@echo "✅ Minishell is ready!"

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all