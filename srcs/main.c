/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:06:27 by dherszen          #+#    #+#             */
/*   Updated: 2024/06/24 18:05:39 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 /*
	Minishell needs to display a prompt when waiting for a new command.

		We need to:

		read_command
		parse_command
		execute_command

		And also:
		verify_command
	*/

// Variável global para controlar a interrupção ou não do prompt
volatile unsigned int	prompt_status = 0;

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		prompt_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

int	main(void)
{
	char				*input;
// 	struct sigaction	sa;
	//struct s_node   minishell_data;

/* 	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handle;
	sigaction(SIGINT, &sa, NULL); */
	setup_signal_handling();
	while (42)
	{
		if (prompt_status)
			prompt_status = 0;
		input = readline("$ ");
		if (input == NULL)
		{
//			printf("\n");
			break ;
		}
		add_history(input);
		printf("You entered: %s\n", input);
		if (ft_strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	clear_history();
	free(input);
	return (EXIT_SUCCESS);
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handle;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		handle_sig_error(SIGINT);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		handle_sig_error(SIGQUIT);
}

void	handle_sig_error(int sig)
{
	if (sig == SIGINT)
	{
		perror(("Error setting up SIGINT handler\n"));
		exit(EXIT_FAILURE);
	}
	else if (sig == SIGQUIT)
	{
		perror(("Error setting up SIGQUIT handler\n"));
		exit(EXIT_FAILURE);
	}
	else
		return ;
}
