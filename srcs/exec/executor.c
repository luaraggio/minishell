/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/24 22:52:31 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int	executor(t_command *command, t_node *sentence)
{
	//t_node	*current_node;
	//int	exit_status;
	(void)*command;

	//current_node = sentence;
	if (has_pipe_or_not(sentence) == TRUE)//Vou criar pipe se existir pipe
		make_pipe(sentence);
	if (is_redirect(command, sentence == TRUE)
		do_redirections();
	//pipe_execution(command, sentence);
	run_commands(command, sentence);
	//limpar tudo;
	//waitpid(current_node->pid, &current_node->exit_status, 0);
	return (NO_ERROR);
}*/

int executor(t_command *command, t_node *sentence)
{
	t_node *current_node;

	if (has_pipe_or_not(sentence) == TRUE)
		make_pipe(sentence);
	current_node = sentence;
	while (current_node)
	{
		/*if (has_redirect(current_node) == TRUE)
			do_redirections(current_node); */
		run_commands(command, current_node);
		current_node = current_node->next;
	}
	current_node = sentence;
	close_node_fds(current_node);
    current_node = sentence;
	wait_cmds(current_node);
	//Dar free no que precisar!!!
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
