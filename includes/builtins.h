/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:08:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/12 16:58:04 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h" // depois tirar ou colocar # include "minishell.h no lugar de # include "builtins.h em cada arquivo das builtins

// struct das variaveis de ambiente. inicializar com as variaveis de ambiente do sistema no inicio do programa
// e mover esse typedef no minishell.h (???)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		ft_echo(char **arg);
int		ft_cd(char **args);
int		ft_pwd(char **args);
int		ft_env(char **envp);

size_t	get_env_size(char **envp);
t_env	*new_env(char *key, char *value);
char	*get_env_key(char *env);
char	*get_env_value(char *env);
t_env	*init_env(char **envp);

#endif
