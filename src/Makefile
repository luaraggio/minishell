NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 

all: $(NAME)

$(NAME):	$(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@echo "✅ Minishell is ready!"

clean:
	rm -f $(NAME)

re: clean all
