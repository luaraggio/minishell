/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/17 11:19:32 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	executor(t_command *command, t_node *sentence)
{
	t_node		*current_node;
	int		ret;

	ret = NO_INFO;
	current_node = sentence;
	while (current_node)
	{
		//Redirect entra aqui!
		if (current_node->next)
			ret = pipe_execution(command, current_node);
		else
			ret = run_commands(command, current_node);
		current_node = current_node->next;
	}
	return (ret);
}

int	run_commands(t_command *command, t_node *node) //Luara: separa em execve e builtin
{
	t_tokens	*current_token;

	current_token = node->token;
	if (current_token->type == BUILTIN)
	{
		//Luara: Fazer um pré-builtins para transformar builtins de matriz p/ lista linkada percorendo t_node!!
		/*Letícia: return (run_builtin(node->token, command->my_env, 1)); -> a função está enviando fd 1 por padrão e
				deverá ser ajustado isso posteriormente para enviar um fd específico*/
		return(printf("Achei um builtin!\n"), NO_ERROR);
	}
	else
		return (run_execve(command, node));
	//return(printf("Não um builtin!\n"), NO_ERROR);
	return (NO_ERROR);
}