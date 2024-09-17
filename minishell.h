/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/17 12:35:13 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/my_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

enum e_flag {
	FALSE = 0,
	TRUE = 1,
	OFF = 2,
	ON = 3
};

enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	MISUSE = 2,
	CANT_EXEC = 126,
	NOT_FOUND = 127,
	INVALID_EXIT_ARG = 128,
	FATAL_ERROR_MINUS_N = 128,
	USED_CTRL_C = 130, // DONE
	EXIT_STATUS_OUT_RANGE = 255,
	CLOSE
};

enum e_ascii {
	DOUBLE_QUOT_MARK = 34,	// "
	SIMPLE_QUOT_MARK = 39,	// '
	PIPE = 124,				// |
	AMPERSAND = 38,			// &
	SEMICOLON = 59,			// ;
	OPEN_PARENTHESIS = 40,	// (
	CLOSE_PARENTHESIS = 41,	// )
	LESS_THAN = 60,			// <
	GREATER_THAN = 62,		// >
	DOLLAR = 36,			//$
	QUESTION_MARK = 63,		//?
	SPACE_CHAR = 32,		// space
	TAB_CHAR = 9,			// \t
	NEWLINE_CHAR = 10,		// \n
	UNPRINT_CHAR = 8
};

enum e_token {
	NO_INFO = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	BUILTIN = 4,
	EXEC = 5,
	T_PIPE = 124, // |
	REDIR_APPEND = 3, // >>
	REDIR_OUT = 62, // >
	REDIR_IN = 60, // <
	REDIR_HEREDOC = 6, // <<
	REDIR_FILE
};

typedef struct s_env	t_env;
typedef struct s_tokens	t_tokens;
typedef struct s_node	t_node;
typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

typedef struct s_tokens
{
	char			*word;
	enum e_token	type;
	t_tokens		*next;
}	t_tokens;

typedef struct s_node
{
	t_tokens	*token;
	int			fd_in;
	int			fd_out;
	pid_t		pid;
	int			exit_status;
	t_node		*next;
}	t_node;

typedef struct s_command
{
	char	*input;
	char	**input_matrix;
	char	*invalid_metas;
	char	*prompt;
	t_node	*l_input;
	t_env	*my_env;
}	t_command;

char	*make_prompt(void);
void	get_env(t_command *command);
t_env	*create_first_env_node(char *c, t_env *list);
t_env	*create_last_env_node(char  *c, t_env *temp);
void	ms_loop(t_command command);
void	set_command(t_command *command);
void	print_env(t_env *list, int fd);
void	change_invalid_metachars(t_command *command);
int		is_metachar(char c);
void	malloc_str_of_invalid_metas(t_command *command);
char	*check_invalid_successive_metachars(char *input);
void	add_meta_to_metastring(t_command *command, int i);
char	*remove_spaces_around_metachars(char *s);
void	remove_spaces_after_metachars(char *s, char *str);
void	remove_spaces_before_metachars(char *s, char *str, int final_size);
char	**meta_split(char const *s);
int		strlen_without_spaces_post_metachars(char *s);
int		strlen_without_spaces_before_metachars(char *s);
char	**return_invalid_metas(t_command *command, char **matrix);
void	return_added_unprinted_chars(char *s, char *metas);
t_env	*my_getenv_by_list(const char *name, t_env *my_env);
void	make_list_from_input(t_command *command);
t_node	*create_first_input_node(char *s, t_node *list);
t_node	*create_last_input_node(char *s, t_node *prev);

// parser
void	parser(t_command *command);
char	**split_sentence_by_char(char *input, char c);
int		is_builtin(char *s);
//char	**split_sentences(char *input);

// is?
int		is_pipe(char c);
int 	is_simple_quote(char c);
int 	is_double_quote(char c);
int		is_append(char *s);
int		is_redir_out(char *s);
int		is_redir_in(char *s);
int		is_heredoc(char *s);
int		is_file(t_node *node, t_node *list);
int		is_redirect(char *str);
int		is_valid_exp_char(char c);
int		is_valid_ev(char *str);
int		is_char(char o, char c);
//int		is_char(char *s, char c);

// list
void	remove_env(t_env *node, t_env *start);
t_tokens    *make_list_tokens(char *s, t_node *list);
void    create_first_input_token(char *word, t_tokens *list);
t_tokens    *create_last_token(char *word, t_tokens *prev);
//void	change_env_value(t_env *node, char *str);
//void	create_new_ev(char *str, t_env *env_list);

// error
int		first_input_validation(t_command *command);

// lexer
void	lexer(t_command *command);
//void	set_token(t_node *node, t_node *first);
//int		is_exec(char *s);
char    **tokenize_sentence(char *input);

// parser
void	search_tokens(t_node *input);
void    set_token(t_tokens *token, int command, int count);
int		is_builtin(char *s);

// Built In
int		run_builtin(t_command *command, t_node *node, int fd);
int		pwd(t_command *command);
void	my_export(t_env *env, t_node *node_i, int fd);
void	print_env_for_export(t_env *list, int fd);
void    my_unset(t_env *env, t_node *node_i);
int		check_export_error(char **str);
char	*validate_quot_marks_for_export(char *str);
int		is_valid_ev(char *str);
void	change_env_value(t_env *env, char *str);
void	create_new_ev(char *str, t_env *env);
int		my_cd(t_node *node, t_env *env);
int		my_echo(t_node *node, int fd);

// Execution
//void	print_env_array(char **envp);
void	free_matrix(char **matrix);
void	execve_clean(char *path, char **env_array);
void	close_fds(int fd_1, int fd_2);
char	*get_path_var(t_command *command);
char	**envp_list_to_array(t_env *env_list);
char	**cmd_list_to_array(t_node *sentences);
char	*get_absolute_path(t_command *command, t_node *list);
int		executor(t_command *command, t_node *sentence);
int		run_commands(t_command *command, t_node *node);
int		run_execve(t_command *command, t_node *list);
int		pipe_execution(t_command *command, t_node *node);
int		env_list_size(t_env *list);
int		count_tokens_in_node(t_node *sentence);

// Clear
void	clear_input(t_command *command);
void    final_clear(t_command *command);
void	free_list(t_node *list);
void	clear_loop_end(t_command *command);
void	free_env(t_env *list);
void	free_sentences(char **sentences);
void	free_tokens(t_tokens *token);

// signals
void	signal_handle(int sig);
void	setup_signal_handling(void);
void	handle_sig_error(int sig);

// variable expansion
void	var_exp(t_command *command);
void	search_dollar(t_tokens *node_token, t_env *env);
int		check_post_dollar(t_tokens *token, char *str, int j, t_env *env);
int		print_global_var(t_tokens *token, char *str, int j);
int		double_dollar(t_tokens *token, char *str, int j);
int		expand_variable(t_tokens *token, t_env *env, char *str, int j);
char	*join_strs(char *str, char *middle, int j, int jump, int *index);

// Teste:

void	printlist(t_node *list);
#endif
