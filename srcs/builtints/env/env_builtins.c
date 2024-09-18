/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/14 23:04:32 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//static void	conditions_to_export(char **str, char **end_str);

void	print_env(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		//my_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

//export

void	my_export(t_env *env, t_tokens *node_t, int fd)
{
	char		*str;
	t_env		*node_env;
	t_tokens	*temp;

	str = NULL;
	node_env = NULL;
	temp = node_t;
	if (node_t == NULL)
	{
		print_env_for_export(env, fd);
		return ;
	}
	while (temp)
	{
		if (is_valid_ev(temp->word) == ERROR)
		{
			temp = temp->next;
			continue ;
		}
		else
		{
			node_env = my_getenv_by_list(temp->word, env);
			str = fromstrcdup(temp->word, '=');
			if (node_env != NULL)
				change_env_value(node_env, str);
			else
				create_new_ev(temp->word, env);
			free(str);
		}
		temp = temp->next;
	}
}

/*
void	my_export(char **str, t_command *command)
{
	t_env	*node;
	char	*new_value;
	char	*end_str;

	if (!*str)
	{
		print_env_for_export(command->my_env);
		return ;
	}
	new_value = NULL;
	end_str = fromstrcdup(*str, '=');
	node = my_getenv_by_list(*str, command->my_env);
	conditions_to_export(str, &end_str);
	if (is_closed_by_quot_marks(end_str) != TRUE)
		new_value = fromstrcdup(*str, '=');
	else
		new_value = my_strdup(*str);
	if (node != NULL)
		change_env_value(node, new_value);
	else
		create_new_ev(*str, command->my_env);
	free(new_value);
	free(end_str);
}

static void	conditions_to_export(char **str, char **end_str)
{
	char	*str2;

	str2 = NULL;
		if (is_closed_by_quot_marks(*end_str) == TRUE)
	{
		str2 = validate_quot_marks_for_export(*end_str);
		free(*str);
		*str = my_strdup(str2);
		free(str2);
	}
	else if (is_there_space(*str) == TRUE)
	{
		str2 = my_strcdup(*str, SPACE_CHAR);
		free(*str);
		*str = my_strdup(str2);
		free(str2);
	}
}*/

// unset

void	my_unset(t_env *env, t_tokens *node_i)
{
	t_env		*node_env;
	t_tokens	*temp;

	temp = node_i;
	node_env = NULL;
	while (temp)
	{
		if (!temp->word)
		{
			temp = temp->next;
			continue ;
		}
		node_env = my_getenv_by_list(temp->word, env);
		if (node_env != NULL)
			remove_env(node_env, env);
		temp = temp->next;
	}
}
