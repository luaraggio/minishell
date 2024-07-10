/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:45 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/10 16:21:12 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h" // trocar depois para "minishell.h"

int	ft_echo(char **args)
{
	if (args[0])
	{
		ft_putstr_fd(args[0], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 2))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
