/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:55:49 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/19 18:51:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
- Abrir os pipes ao percorrer os nós
- Configurar fd dos pipes
- Percorrer nós pra saber se tem redirect e qual redirect
- Ao achar redirect do heredoc, fazer o redirect só do heredoc e depois expandir variáveis
- De acordo com o redirect, configurar os fds que não são de heredoc
- Depois, mandar a estrutura final para a execução
*/

int	pipe_scroll_node(t_command *command, t_node *sentence)
{
	t_node	*current_node;

	current_node = sentence;
	if (!sentence)
	{
		printf("Não há node!\n");
		return (ERROR);
	}
	while (current_node)
	{
		if (current_node->next)
		{

		}
		current_node = current_node->next;
	}
}

int	make_pipe(t_command *command, t_node *sentence)
{
	//quantidade de nós menos um
	int	node_count;

	node_count = 
}
