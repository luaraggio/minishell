/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:58:53 by dherszen          #+#    #+#             */
/*   Updated: 2024/06/21 21:05:51 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
# include <stdlib.h>
# include <signal.h>

//Readline library
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
	char	**str; //input que será splitado (ainda vamos organizar como iremos separar os comandos)
	struct s_node	*next; //ponteiro para a próxima lista para separar os comandos de acordo com '|'(será quando precisaremos usar fork para criar outro processo)
}	t_node;

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

#endif
