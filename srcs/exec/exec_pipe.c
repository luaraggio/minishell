/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/26 02:04:31 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     pipe_execution(t_command *command, t_node *list)
{
    int     pipe_fd[2];
    int     pid_1;
    int     pid_2;

    if (pipe(pipe_fd) == -1)
        return (perror(strerror(errno)), ERROR);
    pid_1 = fork();
    if (pid_1 == -1)
        return (perror("fork"), ERROR);
    if (pid_1 == 0)
    {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 (stdout)");
            exit(ERROR);
        }
        close(pipe_fd[1]);
        run_execve(command, list);
        exit(EXIT_SUCCESS);
    }
    pid_2 = fork();
    if (pid_2 == -1)
        return (perror("fork"), ERROR);

    if (pid_2 == 0)
    {
        close(pipe_fd[1]);
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 (stdin)");
            exit(ERROR);
        }
        close(pipe_fd[0]);
        run_execve(command, list->next->next);
        exit(EXIT_SUCCESS);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);
    return (NO_ERROR);
}
