/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 16:53:53 by lraggio          ###   ########.fr       */
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

enum e_flag
{
	FALSE = 0,
	TRUE = 1,
	OFF = 2,
	ON = 3
};

/*
Valores Padrão:
0: Sucesso. O comando foi executado com sucesso.
1: Erro Geral. Indica uma falha genérica ou um erro não específico.
Erros Comuns:
127: Comando Não Encontrado. Código retornado quando o shell não consegue encontrar o comando especificado. É uma maneira padrão de indicar que o comando não foi encontrado no caminho especificado.
Outros Valores:
2-125: Podem ser utilizados por comandos e programas para indicar erros específicos. Esses valores são definidos pelos próprios programas e podem variar.
126: Comando Não Executável. Esse código indica que o comando foi encontrado, mas não é executável (por exemplo, se não tiver permissões de execução).
128: Usado para indicar que o comando foi terminado por um sinal. O código de saída é o número do sinal adicionado a 128 (por exemplo, 128 + 2 para SIGINT).

0: Success—Indicates that the command or program executed successfully without any errors.
1: General Error—A catch-all exit code for a variety of general errors. Often used when the command or program encounters an error, but no specific exit code is available for the situation.
2: Misuse of shell built-ins—Indicates incorrect usage of shell built-in commands or misuse of shell syntax.
126: Command cannot execute—The command was found, but it could not be executed, possibly due to insufficient permissions or other issues.
127: Command not found—The command was not found in the system's PATH, indicating that either the command does not exist or the PATH variable is incorrectly set.
128: Invalid exit argument—Returned when a script exits with an invalid argument. This usually indicates an error in the script itself.
128 + N: Fatal error signal N—Indicates that the command or program was terminated by a fatal error signal. For example, an exit code of 137 (128 + 9) means that the command was terminated by a SIGKILL signal.
130: Script terminated by Control-C—Indicates that the command or script was terminated by the user using Control-C (SIGINT signal).
255: Exit status out of range—Returned when the exit status is outside the valid range (0 to 254).
*/

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


//------------------MAIN------------------
//main.c
int		main(int argc, char *argv[]);
//prompt_and_inputs.c
void	set_command(t_command *command);
char	*make_prompt(void);
//pre_exec.c
void	pre_exec(t_command   *command);

//------------------PARSER------------------
//parser.c
int		parser(t_command *command);
char	**split_sentence_by_char(char *input, char c);
char	**tokenize_sentence(char *input);
//tokenize_words.c
void	search_tokens(t_node *input);
void    set_token(t_tokens *token, int command, int count);
int		is_builtin(char *s);
//LINKED_LIST_INPUT
//create_list_input.c
t_tokens	*make_list_tokens(char *s, t_node *list);
void	make_list_from_input(t_command *command);
void	free_sentences(char **sentences);
void	free_tokens(t_tokens *token);

//------------------ERROR_HANDLE------------------
//input_validation.c
int		first_input_validation(t_command *command);
int		general_input_validation(t_node *node);
//pipe_validation.c
int		check_pipe_init_and_end(char *str);
int		check_double_pipe_together(char **str);
int		check_following_pipes(char *str);
char	*remove_after_double_pipe(char **str, int i);
//print_error.c
void	print_error(char *str);
//quote_validation.c
int		n_quote_validation(char *str);
int		dollar_is_closed_by_single_quote(char **str);
//remove_quotes.c
void	remove_all_quotes(t_node *list, int quote);
void	remove_quote(char **str, int i, enum e_ascii quote);

//----------------GENERAL_FUNCTIONS------------------
//is_chars_functions.c
int		is_pipe(char c);
int 	is_simple_quote(char c);
int 	is_double_quote(char c);
int		is_append(char *s);
int		is_valid_exp_char(char c);
int		is_char(char o, char c);
//is_chars_functions_2.c
int		is_redir_out(char *s);
int		is_redir_in(char *s);
int		is_heredoc(char *s);
int		is_redirect(char *str);

//---------------------SIGNALS---------------------
//signal_handle.c
void	signal_handle(int sig);
void	setup_signal_handling(void);
void	handle_sig_error(int sig);

//-----------------LINKED_LIST---------------------
//change_list.c
void	remove_env(t_env *node, t_env *start);
//list_functions.c
void	create_first_input_token(char *word, t_tokens *list);
t_env	*create_first_env_node(char *c, t_env *list);
t_env	*create_last_env_node(char  *c, t_env *temp);
t_node	*create_first_input_node(char *s, t_node *list);
t_node	*create_last_input_node(char *s, t_node *prev);
t_tokens	*create_last_token(char *word, t_tokens *prev);
//                  Teste:
void	printlist(t_node *list);

//-----------------VARIABLE_EXPANSION---------------------
//var_exp.c
void	var_exp(t_command *command);
void	search_dollar(t_tokens *node_token, t_env *env);
int		check_post_dollar(t_tokens *token, char *str, int j, t_env *env);
//var_exp_utils.c
int		print_global_var(t_tokens *token, char *str, int j);
int		double_dollar(t_tokens *token, char *str, int j);
int		expand_variable(t_tokens *token, t_env *env, char *str, int j);
char	*join_strs(char *str, char *middle, int j, int jump, int *index);

//---------------------------ENV-----------------------
//env_utils.c
void	get_env(t_command *command);
t_env	*my_getenv_by_list(const char *name, t_env *my_env);

//---------------------EXEC-----------------------
//clean_execve.c
void	execve_clean(char *path, char **env_array);
void	free_matrix(char **matrix);
//executor.c
int		executor(t_command *command, t_node *sentence);
int		run_commands(t_command *command, t_node *node);
//execve_utils.c
int		env_list_size(t_env *list);
int		count_tokens_in_node(t_node *sentence);
//init_execve.c
char	**envp_list_to_array(t_env *env_list);
char	**cmd_list_to_array(t_node *sentences);
char	*get_executable_path(t_command *command, t_node *list);
//pipe_execution.c
int		pipe_execution(t_command *command, t_node *node);
//run_execve.c
int		run_execve(t_command *command, t_node *list);
//fd.c
void	close_fds(int fd_1, int fd_2);
//redirect.c

//------------------------BUILTINS-----------------------
//builtins.c
int		run_builtin(t_command *command, t_tokens *token, t_env *env, int fd);
//cd.c
int		my_cd(t_tokens *node, t_env *env);
//echo.c
int		my_echo(t_tokens *node, int fd);
//exit.c
int		my_exit(t_tokens *token, t_command *command);
//pwd.c
int		pwd(void);
//ENV
//env_bt_utils.c
void	print_env_for_export(t_env *list, int fd);
void	change_env_value(t_env *env, char *str);
void	create_new_ev(char *str, t_env *env);
int		is_valid_ev(char *str);
//env_builtins.c
void	print_env(t_env *list, int fd);
void	my_export(t_env *env, t_tokens *node_t, int fd);
void	my_unset(t_env *env, t_tokens *node_i);

//------------------------CLEANING-----------------------
//clear_funct.c
void	clear_loop_end(t_command *command);
void	clear_input(t_command *command);
void	final_clear(t_command *command);
void	free_list(t_node *list);
void	free_env(t_env *list);

#endif
