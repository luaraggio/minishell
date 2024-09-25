/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/24 22:16:35 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    t_node      *node;
    char        *path;
    char        **env_array;
    char        **args;

    env_array = envp_list_to_array(command->my_env);
    path = get_executable_path(command, list);
    node = list;
    args = cmd_list_to_array(node);
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->fd_out != STDOUT_FILENO)
        {
            if (dup2(node->fd_out, STDOUT_FILENO) == -1)
            {
                perror("dup2 fd_out");
                execve_clean(path, env_array);
                free_matrix(args);
                exit(ERROR);
            }
        }
        if (node->fd_in != STDIN_FILENO)
        {
            if (dup2(node->fd_in, STDIN_FILENO) == -1)
            {
                perror("dup2 fd_in");
                execve_clean(path, env_array);
                free_matrix(args);
                exit(ERROR);
            }
        }
        if (execve(path, args, env_array) == -1)
        {
            //perror("execve");
            execve_clean(path, env_array);
            free_matrix(args);
            exit(127);  // Retorna erro se o comando não for encontrado
        }
        /*if (node->fd_out != STDOUT_FILENO)
			dup2(node->fd_out, STDOUT_FILENO);
		if (node->fd_in != STDIN_FILENO)
			dup2(node->fd_in, STDIN_FILENO);
        if (execve(path, args, env_array) == -1)
            return (execve_clean(path, env_array), free_matrix(args), exit(127), ERROR);*/
    }
    waitpid(node->pid, &node->exit_status, 0);
	//waitpid(node->pid, &list->exit_status, 0);
    return (NO_ERROR);
}

/*int run_execve(t_command *command, t_node *node)
{
    char **env_array;
    char *path;
    char **args;

    // Converte a lista de variáveis de ambiente para um array
    env_array = envp_list_to_array(command->my_env);

    // Obtém o caminho do executável
    path = get_executable_path(command, node);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", node->token->word);
        return (ERROR);
    }

    // Converte a lista de argumentos para um array
    args = cmd_list_to_array(node);

    // Cria o processo filho
    node->pid = fork();
    if (node->pid == 0)  // Processo filho
    {
        // Redireciona saída para o pipe, se necessário
        if (node->fd_out != STDOUT_FILENO)
        {
            if (dup2(node->fd_out, STDOUT_FILENO) == -1)
            {
                perror("dup2 fd_out");
                execve_clean(path, env_array);
                free_matrix(args);
                exit(ERROR);
            }
        }

        // Redireciona entrada para o pipe, se necessário
        if (node->fd_in != STDIN_FILENO)
        {
            if (dup2(node->fd_in, STDIN_FILENO) == -1)
            {
                perror("dup2 fd_in");
                execve_clean(path, env_array);
                free_matrix(args);
                exit(ERROR);
            }
        }

        // Executa o comando com execve
        if (execve(path, args, env_array) == -1)
        {
            perror("execve");
            execve_clean(path, env_array);
            free_matrix(args);
            exit(127);  // Retorna erro se o comando não for encontrado
        }
    }
    else if (node->pid > 0)  // Processo pai
    {
        // Espera pelo processo filho
        waitpid(node->pid, &node->exit_status, 0);
    }
    else
    {
        // Erro no fork
        perror("fork");
        execve_clean(path, env_array);
        free_matrix(args);
        return (ERROR);
    }

    // Limpeza no processo pai
    execve_clean(path, env_array);
    free_matrix(args);

    return (NO_ERROR);
}*/
