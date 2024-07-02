/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:58:53 by dherszen          #+#    #+#             */
/*   Updated: 2024/06/23 18:04:14 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <signal.h>
# include <unistd.h> //execv function
# include <sys/wait.h>

//Readline library
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	struct s_node	*next;
}	t_token;

typedef struct s_minishell
{
	char	*input;
	char	**args;
	char	**envp;
	struct s_node	*token;
}	t_minishell;

enum	e_token
{
	CMD,
	ARG,
	PIPE,
	HEREDOC,
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

void	setup_signal_handling(void);
void	signal_handle(int sig);
void	handle_sig_error(int sig);
#endif
