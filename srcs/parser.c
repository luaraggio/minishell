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
    int quote_state;
    int i;
    
    quote_state = 0;
    i = 0;
    while (input[i])
    {
            if (is_simple_quote(input[i]) && (quote_state == 0 || quote_state == 1))
                quote_state ^= 1;
            else if (is_double_quote(input[i]) && (quote_state == 0 || quote_state == 2))
                quote_state ^= 2;
            else if (is_pipe(input[i]) && quote_state == 0) //sem aspas ao redor do pipe
                    input[i] = ALT_PIPE;
            i++;
    }
    return (ft_split(input, ALT_PIPE));
}

/*int ft_parser(char *input, int i)
{
    int i;
    struct s_sentence *sentence_array;
	char             **sentences;

	sentences = split_sentences(input);
	free(input);
	if (!sentences)
		return (printf("Deu erro na expansão de pipe OU não tem pipe\n"), 1);
    sentence_array = malloc(sizeof(t_sentence) * (i + 1));
    if (!sentence_array)
    {
        free(sentence_array);
        return (NULL);
    }
    i = 0;
    while (sentence_array->words != NULL)
    {
        sentence_array[i];
        i++;
    }
	return (0);
}
*/