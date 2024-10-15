/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:29:59 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:24:40 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*take_name_var(char *str, int j);

/**
 * @brief Replaces a token's word with the string representation of the global
 * status.
 *
 * This function converts the global exit status (stored in `g_status`)
 * to a string using `my_itoa`, then joins it to the provided string `str`.
 * It updates the token's word with this new string and frees the old word.
 * This is useful for expanding the "$?" variable in the shell context.
 *
 * @param token The token whose word will be replaced.
 * @param str The string to which the global status will be appended.
 * @param j The index for inserting the global status.
 * @return The updated index after the insertion.
 */

int	print_global_var(t_tokens *token, char *str, int j)
{
	char	*number;
	char	*temp;
	int		index;

	number = my_itoa(g_status(-1));
	index = my_strlen(number);
	temp = join_strs(str, number, (j - 1), 1, &index);
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	free(number);
	return (index);
}

/**
 * @brief Handles the expansion of the "$$" variable.
 *
 * This function creates a token with the string representation of the current
 * process ID (PID) by joining the original string `str` with the "$" character.
 * It replaces the token's word and updates the index to reflect the new length.
 * This is crucial for implementing process identification within the shell.
 *
 * @param token The token to be updated with the new PID.
 * @param str The original string that will include the PID.
 * @param j The index for inserting the "$" character.
 * @return The updated index after the insertion.
 */

int	double_dollar(t_tokens *token, char *str, int j)
{
	int		index;
	char	*temp;

	index = 0;
	temp = join_strs(str, "$", (j - 1), 1, &index);
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	index++;
	return (index);
}

/**
 * @brief Expands a variable from the environment based on a token.
 *
 * This function retrieves the variable name from the provided string `str`,
 * looks up its value in the environment using `my_getenv_by_list`, and updates
 * the token's word with the corresponding value. If the variable is not found,
 * an empty string is assigned. Memory is managed to prevent leaks.
 *
 * This function is key for variable expansion in a minishell, allowing
 * user-defined and environment variables to be utilized within commands.
 *
 * @param token The token to be updated with the variable's value.
 * @param env The linked list of environment variables.
 * @param str The string that contains the variable name.
 * @param j The index at which the variable name begins.
 * @return The updated index after the expansion, or ERROR on failure.
 */

int	expand_variable(t_tokens *token, t_env *env, char *str, int j)
{
	int		index;
	char	*temp;
	char	*key;
	t_env	*node;

	index = 0;
	key = take_name_var(str, j);
	node = my_getenv_by_list(key, env);
	if (!node || (my_str_end_cmp(node->key, key) != 0))
	{
		temp = join_strs(str, "", (j - 1), (my_strlen(key)), &index);
		index = my_strlen(key) - 1;
	}
	else
	{
		temp = join_strs(str, node->value, (j - 1), (my_strlen(node->key)),
				&index);
		if (!temp)
			return (free(key), ERROR);
	}
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	free(key);
	return (index);
}

/**
 * @brief Joins multiple strings together, managing memory dynamically.
 *
 * This function constructs a new string by joining the original string `str`
 * with a middle string `middle` at a specified index `j`. It manages
 * memory allocation carefully to ensure no leaks occur. The resulting string
 * is returned. This is essential for constructing command strings in the
 * minishell.
 *
 * @param str The base string to be joined.
 * @param middle The string to insert into the base string.
 * @param j The index for insertion in the base string.
 * @param jump The amount to skip in the base string.
 * @param index A pointer to store the new index after joining.
 * @return A dynamically allocated string representing the joined result.
 */

char	*join_strs(char *str, char *middle, int j, int jump, int *index)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		size_temp1;

	temp3 = NULL;
	temp1 = my_strldup(str, j);
	temp2 = my_strjoin(temp1, middle);
	size_temp1 = my_strlen(temp1);
	if ((int)my_strlen(str) != (size_temp1 + jump))
	{
		free(temp1);
		temp1 = fromstrldup(str, size_temp1 + jump);
		temp3 = my_strjoin(temp2, temp1);
		*index = my_strlen(temp2) - 1;
	}
	else
		temp3 = strdup(temp2);
	free(temp1);
	free(temp2);
	return (temp3);
}

/**
 * @brief Extracts the name of a variable from a string.
 *
 * This function retrieves the name of a variable from the provided string `str`
 * starting at index `j`. It identifies valid variable characters (letters,
 * digits, or underscores) and returns a dynamically allocated string containing
 * the variable name. This is essential for correctly parsing variable names in
 * minishell.
 *
 * @param str The string from which to extract the variable name.
 * @param j The starting index for extraction.
 * @return A dynamically allocated string representing the variable name,
 *         or NULL on memory allocation failure.
 */

static char	*take_name_var(char *str, int j)
{
	int		i;
	int		size;
	char	*name;

	i = j;
	size = 0;
	while (str[i] && (my_isalpha(str[i]) != 0 || my_isdigit(str[i]) != 0
			|| str[i] == '_'))
	{
		size++;
		i++;
	}
	name = (char *)malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	size = 0;
	while (str[j] && j < i)
	{
		name[size] = str[j];
		size++;
		j++;
	}
	name[size] = '\0';
	return (name);
}
