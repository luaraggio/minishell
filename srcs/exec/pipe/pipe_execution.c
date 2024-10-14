/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/13 19:24:51 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_path(t_command *cmd, t_node *node, char **env_array)
{
	if (access(node->token->word, (F_OK | X_OK)) != 0)
	{
		if (errno == EACCES)
		{
			do_dup2(node);
			close_node_fds(node);
			print_errno(node);
			free_matrix(env_array);
			return (free_matrix(env_array), NULL);
		}
		return (get_executable_path(cmd, node));
	}
	else
		return (node->token->word);
}

void	run_pipe_execve(t_command *command, t_node *list)
{
	t_node	*node;
	t_node	*temp;
	char	*path;
	char	**env_array;
	char	**args;

	node = list;
	env_array = envp_list_to_array(command->my_env);
	path = check_path(command, node, env_array);
	if (!path)
		return (close_all_node_fds(node), free_matrix(env_array));
	args = cmd_list_to_array(node);
	do_dup2(node);
	temp = node;
	close_all_node_fds(temp);
	execve(path, args, env_array);
	if (path != node->token->word)
		free(path);
	execve_clean(args, env_array);
	return ;
}

int	run_pipe_builtin(t_command *command, t_tokens *token, t_env *env, int fd)
{
	int	ret;

	ret = 0;
	if (my_strcmp(token->word, "echo") == 0)
		ret = my_echo(token->next, fd);
	else if (my_strcmp(token->word, "cd") == 0)
		ret = my_cd(token->next, env);
	else if (my_strcmp(token->word, "pwd") == 0)
		ret = pwd();
	else if (my_strcmp(token->word, "export") == 0)
		my_export(env, token->next, fd);
	else if (my_strcmp(token->word, "unset") == 0)
		my_unset(env, token->next);
	else if (my_strcmp(token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(token->word, "exit") == 0)
		ret = my_exit(token->next, command);
	return (ret);
}

int	pipe_execution(t_command *command, t_node *node)
{
	int	ret;

	ret = NO_ERROR;
	node->pid = fork();
	if (node->pid == 0)
	{
		if (node->token->type != BUILTIN)
			run_pipe_execve(command, node);
		else
		{
			if (node->fd_in != STDIN_FILENO)
				dup2(node->fd_in, STDIN_FILENO);
			if (node->fd_out != STDOUT_FILENO)
				dup2(node->fd_out, STDOUT_FILENO);
			ret = run_pipe_builtin(command, node->token,
					command->my_env, node->fd_out);
			close_all_node_fds(node);
		}
		ret = node->exit_status;
		clear_loop_end(command);
		final_clear(command);
		exit(ret);
	}
	return (ret);
}
