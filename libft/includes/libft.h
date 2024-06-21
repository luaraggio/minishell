/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:54:09 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 17:07:49 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

// gnl macros
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4242
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

// struct libft bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// struct gnl
typedef struct s_glist
{
	char			*content;
	struct s_glist	*next;
}	t_glist;

// libft functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// ft_printf functions
int		ft_printf(const char *format, ...);
int		ft_putchar_i(char c);
int		ft_putstr_i(char *s);
int		ft_putnbrs_i(int n);
int		ft_putnbru_i(unsigned int n, char *lst);
int		ft_putptr_i(unsigned long n, int index);

// gnl functions
char	*get_next_line(int fd);
char	*get_next_line_fd(int fd);
void	read_and_store(int fd, t_glist **storage);
void	add_to_storage(t_glist **storage, char *chars_read, int n_read);
void	extract_line_to_print(t_glist *storage, char **line);
void	remove_printed_line(t_glist **storage);
ssize_t	ft_strlen_gnl(const char *s);
int		new_line_not_present(t_glist *storage);
t_glist	*ft_lst_last(t_glist *storage);
void	malloc_line(char **line, t_glist *storage);
void	free_storage(t_glist *storage);

#endif
