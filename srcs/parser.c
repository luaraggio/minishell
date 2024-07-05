/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:54:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/07/02 19:16:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **split_sentences(char *input)
{
/*

Procura pipes que vão funcionar exatamente como pipes, não como caractere '|' 
dentro de aspas "" ou ''. Ao encontrar o pipe funcional, substitui por outro 
caractere (aqui estarei usando um caractere não printável que será ignorado
na tokenização) para que na split, possamos passar esse caractere como parâ-
metro. Assim, não perdemos os "pipes caracteres" de vista.

Essa função lê a string input e verifica concomitantemente 3 aspectos: a presença de aspas (que na primeira passada seta a flag pra != 0- com a numeração específica de aspas simples (1) ou aspas duplas (2)- o fechamento dessas aspas (se estão em pares ou não) e, por último, vê se o pipe está fora de aspas duplas e simples fechadas (ex. "|" ou '"|"').

Obs: " blablabla -> comando da minishell não funcionará
    blablabla ' -> comando da minishell não funcionará

*/
    int quote_state;
    int i;
    
    quote_state = 0;
    i = 0;
    while (input[i])
    {
            if (simple_quote(input[i]) && (quote_state == 0 || quote_state == 1))
                quote_state ^= 1;
            else if (double_quote(input[i]) && (quote_state == 0 || quote_state == 2))
                quote_state ^= 2;
            else if (is_pipe(input[i]) && quote_state == 0) //sem aspas ao redor do pipe
                    input[i] = ALT_PIPE;
            i++;
    }
    return (ft_split(input, ALT_PIPE));
}

int ft_parser(char *input)
{
    //struct s_sentence *sentence_array;
	char             **sentences;

	sentences = split_sentences(input);
	free(input);
	if (!sentences)
		return (printf("Deu erro na expansão de pipe OU não tem pipe\n"), 1);
	return (0);
}