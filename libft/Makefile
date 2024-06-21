
NAME		= libft.a

AUTHOR		= "Daniel Herszenhaut <dherszen@student.42.rio>"

C_PATH		= ./srcs/

LIBFT_SRCS	= ft_atoi.c         \
              ft_bzero.c        \
              ft_calloc.c       \
              ft_isalnum.c      \
              ft_isalpha.c      \
              ft_isascii.c      \
              ft_isdigit.c      \
              ft_isprint.c      \
              ft_memchr.c       \
              ft_memcmp.c       \
              ft_memcpy.c       \
              ft_memmove.c      \
              ft_memset.c       \
              ft_strchr.c       \
              ft_strdup.c       \
              ft_strjoin.c      \
              ft_strlcat.c      \
              ft_strlcpy.c      \
              ft_strlen.c       \
              ft_strcmp.c       \
              ft_strncmp.c      \
              ft_strnstr.c      \
              ft_strrchr.c      \
              ft_strtrim.c      \
              ft_substr.c       \
              ft_tolower.c      \
              ft_toupper.c      \
              ft_split.c        \
              ft_itoa.c         \
              ft_strmapi.c      \
              ft_striteri.c     \
              ft_putchar_fd.c   \
              ft_putstr_fd.c    \
              ft_putendl_fd.c   \
              ft_putnbr_fd.c    \
              ft_lstnew_bonus.c        \
              ft_lstadd_front_bonus.c  \
              ft_lstsize_bonus.c       \
              ft_lstlast_bonus.c       \
              ft_lstadd_back_bonus.c   \
              ft_lstdelone_bonus.c     \
              ft_lstclear_bonus.c      \
              ft_lstiter_bonus.c       \
              ft_lstmap_bonus.c

FT_PRINTF_SRCS	= ft_printf.c       \
                  ft_putstr_i.c     \
                  ft_putnbr_i.c

GNL_SRCS        = get_next_line.c   \
                  get_next_line_fd.c   \
                  get_next_line_utils.c

C_SRCS		= ${LIBFT_SRCS} ${FT_PRINTF_SRCS} ${GNL_SRCS}

H_SRCS		= ./includes

C_OBJS		= ${addprefix ${C_PATH}, ${C_SRCS:.c=.o}}

RM			= rm -f

CC			= cc

C_FLAGS		= -Wall   \
        	  -Wextra \
        	  -Werror

AR_FLAGS	= rcs

AR			= ar ${AR_FLAGS}

BONUS_OBJS	= ${addprefix ${C_PATH}, ${BONUS_SRCS:.c=.o}}

.c.o:
			${CC} ${C_FLAGS} -c $< -o ${<:.c=.o} -I${H_SRCS}

${NAME}:	${C_OBJS}
			${AR} ${NAME} ${C_OBJS} ${BONUS_OBJS}

all:		${NAME}

clean:
			${RM} ${C_OBJS} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
