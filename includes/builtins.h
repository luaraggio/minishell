/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:08:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/11 11:54:23 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h" // depois tirar ou colocar # include "minishell.h no lugar de # include "builtins.h em cada arquivo das builtins

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

int	ft_echo(char **arg);
int	ft_cd(char **args);
int	ft_pwd(char **args);
int	ft_env(char **envp);

#endif
