NAME = minishell

AUTHOR          = "Daniel Herszenhaut <dherszen@student.42.rio> and Luara Raggio <lraggio@student.42.rio>"

RED				= \033[0;31m
BLUE			= \033[0;34m
GREEN			= \033[0;32m
NO_COLOR		= \033[0m

# Mandatory files and paths
H_SRCS          = ./includes
SRCS_PATH       = ./srcs
OBJS_PATH       = ./objs
C_SRCS 			= main.c \
				  grammar.c \
				  parser.c \
				  parser_utils.c \
				  signal_handle.c

C_OBJS		   = ${addprefix ${OBJS_PATH}/, ${C_SRCS:.c=.o}}

# libft
LIBFT_PATH      = ./libft
LIBFT           = ${LIBFT_PATH}/libft.a

# Remove files
RM              = rm -f

# compiler and compiler flags
CC              = cc
C_FLAGS        ?= -Wall   \
                  -Wextra \
                  -Werror \
                  -ggdb3  \

RL_FLAGS = -lreadline \

OS := $(shell uname)
ifeq ($(OS), Darwin)

C_FLAGS += -I$(shell brew --prefix readline)/include
RL_FLAGS += -L$(shell brew --prefix readline)/lib
endif

# Default c.o. rule
${OBJS_PATH}/%.o: ${SRCS_PATH}/%.c
				@mkdir -p $(@D)
				@${CC} ${C_FLAGS} -c $< -o $@ -I${H_SRCS}

all:			${NAME}

${NAME}:		${LIBFT} ${C_OBJS}
				@${CC} ${C_FLAGS} ${C_OBJS} -o ${NAME} -I${H_SRCS} ${LIBFT} ${RL_FLAGS} && echo "✅ ${BLUE}${NAME}${GREEN} has been compiled!${NO_COLOR}" || echo "❌ ${BLUE}${NAME}${RED} failed to compile${NO_COLOR}"

# Rule for building libft
libft:			${LIBFT}

${LIBFT}:
				@make -C ${LIBFT_PATH} all > /dev/null && echo "✅ ${BLUE}Libft ${GREEN}compilation successful!${NO_COLOR}" || echo "❌ ${RED}Libft compilation failed!${NO_COLOR}"

# Clean targets
clean:
	@make -C ${LIBFT_PATH} fclean > /dev/null && echo "✅ ${BLUE}Libft ${GREEN}files successful deleted!${NO_COLOR}" || echo "❌ ${RED}Libft files deleting failed!${NO_COLOR}"
	@${RM} -rf ${OBJS_PATH} && echo "✅ ${GREEN}All ${BLUE}${NAME} ${GREEN}objects erased!${NO_COLOR}" || echo "❌ ${RED}All ${BLUE}${NAME} ${RED} objects erasing failed!${NO_COLOR}"

fclean: clean
	@${RM} ${NAME} && echo "✅ ${BLUE}${NAME} ${GREEN}binaries erased!${NO_COLOR}" || echo "❌ ${BLUE}${NAME} ${RED}binaries erasing failed!${NO_COLOR}"

re: fclean all

valgrind: $(NAME)
			valgrind --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp ./$(NAME)

.PHONY: all clean fclean re
