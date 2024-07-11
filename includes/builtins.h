/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:08:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/11 11:34:21 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h" // depois tirar ou colocar # include "minishell.h no lugar de # include "builtins.h em cada arquivo das builtins

int	ft_echo(char **arg);
int	ft_cd(char **args);
int	ft_pwd(char **args);


#endif
