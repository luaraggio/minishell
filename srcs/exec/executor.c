/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/28 17:28:29 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if (has_redirect(current_node) == TRUE)
		do_redirections(current_node);*/

int executor(t_command *command, t_node *sentence)
{
	t_node *current_node;
	(void)*command;

	if (is_there_space(sentence->token->word))
		return (print_cmd_not_found(sentence), NO_ERROR);
	if (has_pipe_or_not(sentence) == TRUE)
		make_pipe(sentence);
	current_node = sentence;
	/*if (has_redirect(current_node) == TRUE)
		do_redirections(current_node);*/
	while (current_node)
	{
		if (!current_node->next)
			run_simple_commands(command, current_node);
		else
			run_pipe_commands(command, current_node);
		//close_node_fds(current_node);
		current_node = current_node->next;
	}
	//wait_cmds(current_node);
    return (NO_ERROR);
}

void	run_simple_commands(t_command *command, t_node *node)
{
	t_node	*current_node;

	current_node = node;
	if (current_node->token->type == BUILTIN)
		run_builtin(command, current_node->token, command->my_env, STDOUT_FILENO);
	else
		run_execve(command, current_node);
}
