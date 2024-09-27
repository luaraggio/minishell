/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/27 00:34:17 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int executor(t_command *command, t_node *sentence)
{
	t_node *current_node;

	if (is_there_space(sentence->token->word))
		return (print_cmd_not_found(sentence), NO_ERROR);
	if (has_pipe_or_not(sentence) == TRUE)
		make_pipe(sentence);
	current_node = sentence;
	while (current_node)
	{
		/*if (has_redirect(current_node) == TRUE)
			do_redirections(current_node);*/
		if (!current_node->next)
			run_commands(command, current_node);
		else
			pipe_execution(command, current_node);
		current_node = current_node->next;
	}
	close_node_fds(current_node);
	//wait_cmds(current_node);
	//Ver se preciso dar free aqui!!!
    return (NO_ERROR);
}

int	run_commands(t_command *command, t_node *node)
{
	t_tokens	*current_token;

	current_token = node->token;
	if (current_token->type == BUILTIN) //a função está enviando fd 1 por padrão. deverá ser ajustado isso posteriormente para enviar um fd específico
		return (run_builtin(command, node->token, command->my_env, 1), NO_ERROR);
	else
		return (run_execve(command, node), NO_ERROR);
	return (ERROR);
}
