/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 22:19:37 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile unsigned int    g_status;

void	ms_loop(t_command command)
{
	while (42)
	{
		printf("g_status = %i\n", g_status);
		set_command(&command);
		if (command.input == NULL)
		{
			clear_input(&command);
			break ;
		}
		else if (my_strlen(command.input) == 0)
		{
			clear_input(&command);
			continue ;
		}
		add_history(command.input);
		if (parser(&command) == ERROR)
			continue ;
		post_parser(&command);
		if (executor(&command, command.l_input) == ERROR)
		{
			clear_loop_end(&command);
			break ;
		}
		clear_loop_end(&command);
	}
}

int	main(int argc, char *argv[])
{
	t_command	command;

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
		return (print_no_such_file(argv), ERROR);
	setup_signal_handling();
	get_env(&command);
	ms_loop(command);
	final_clear(&command);
}
