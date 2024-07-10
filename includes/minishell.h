/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:58:53 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/10 16:12:16 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "builtins.h"
# include <stdlib.h>
# include <signal.h>
# include <unistd.h> //execv function
# include <sys/wait.h>

//Readline library
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

enum	e_substitution
{
	ALT_PIPE = 1, // |
	ALT_OUT,     // >
	ALT_IN,      // <
	ALT_APPEND,  // >>
	ALT_HEREDOC, // <<
};

enum	e_token
{
	OUT = 1, //>
	IN, //<
	APPEND, //>>
	HEREDOC, //<<
	CMD,
	ARG,
};

enum	e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

typedef struct s_token
{
	char	*token_content; //conteúdo do token em si
	enum e_token	type; //tipo de token
	struct s_token	*next; //ponteiro para o próximo token
}	t_token;

typedef struct s_sentence
{
	struct s_token	*words;
	int	fd_in;
	int	fd_out;
	pid_t	pid;

}	t_sentence;

typedef struct s_minishell
{
	char	**sentences;
	int		len_sentences;
}	t_minishell;


void	setup_signal_handling(void);
void	signal_handle(int sig);
void	handle_sig_error(int sig);
void	*get_sentences(char *input);
char    **split_sentences(char *input);
//int 	ft_parser(char *input, int i);
int 	is_pipe(char c);
int 	is_simple_quote(char c);
int 	is_double_quote(char c);
//int 	is_space_or_tab(int c);
//int	is_metachar(char c);
#endif
