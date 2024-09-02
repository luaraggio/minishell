/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/27 21:32:51 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile unsigned int    g_status;

int	main(int argc, char *argv[])
{
	t_command	command;

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
	{
		my_printf("bash: %s: No such file or directory\n", argv[1]);
		return 0;
	}
	setup_signal_handling();
	get_env(&command);
	while (42)
	{
		set_command(&command);
		if (command.input == NULL)
		{
			clear_input(&command);
			break;
		}
		if (my_strlen(command.input) == 0)
		{
			clear_loop_end(&command);
			continue;
		}
		add_history(command.input);
		input_parser(&command);
		lexer(&command);
		if (run_commands(&command) == CLOSE)
		{
			clear_loop_end(&command);
			break ;
		}
		clear_loop_end(&command);
	}
	final_clear(&command);
}

/*int		is_space(char c)
{
	return (c == ' ');
}


int		is_all_whitespace(const char *str)
{
	while (*str)
	{
		if (is_space(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}*/
