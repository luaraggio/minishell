/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:06:27 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/02 18:53:36 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

volatile unsigned int	g_status; a global variable to Handle $? -> which should 
expand to the exit status of the most recently executed foreground pipeline.

*/

void	*get_sentences(char *input)
{
	char	**sentences;
	int	i;

	sentences = split_sentences(input);
	i = 0;
	while (sentences[i])
	{
		printf("Sentença[%d]: %s\n", i, sentences[i]);
		i++;
	}
	return (0);
}

int	main(void)//int argc, char **argv, char **envp)
{
	char	*input;
	setup_signal_handling();
	//inicializar ac, av e envp
	printf("Antes do loop\n");
	while (42)
	{
		input = readline("minishell>$ ");
		if (input == NULL)
			break ;
		add_history(input);
		get_sentences(input);
		parser_input(input);
		/*
			expander
			executor
		*/
		free(input); //cleaner
	}
	clear_history();
	//dar free na matriz de struct s_sentence!!!
	return (EXIT_SUCCESS);
}