/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:27:42 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/12 16:49:39 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **envp) // precisa mudar para usar a linked list de envs
{
	while (*envp)
	{
		ft_putstr_fd(*envp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		envp++;
	}
	return (EXIT_SUCCESS);
}
