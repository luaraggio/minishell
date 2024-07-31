/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/31 00:29:44 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_env(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		my_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

//export

void	my_export(char **str, t_command *command)
{
	t_node	*node;
	char	*end_str;
	char	*str2;
	char	*new_value;

	str2 = NULL;
	if (!*str)
	{
		print_env_for_export(command->my_env);
		return ;
	}
	node = my_getenv_by_list(*str, command->my_env);
//	printf("Passou da my_getenv_by_list e está com str = |%s|\n", *str);
	end_str = fromstrcdup(*str, '=');
//	printf("Salvou informações em end_str e vai verificar aspas com str = |%s| e c end_str = |%s|\n", *str, end_str);
	if (is_closed_by_quot_marks(end_str) == TRUE) // ainda ta salvando com aspas
	{
		printf("Verificou que está fechado por aspas e vai entrar na validate_quot_marks_for_export com str = |%s| e c end_str = |%s|\n", *str, end_str);
		str2 = validate_quot_marks_for_export(end_str); // Eu não estou liberando a memória desse str2. Eu teria que utilizar isso em algum lugar??
	}
	else if (is_there_space(*str) == TRUE)
	{
//		printf("Verificou que tem espaços e vai entrar na my_strcdup c str = |%s|\n", *str);
		str2 = my_strcdup(*str, SPACE_CHAR);
		free(*str);
		*str = my_strdup(str2);
//		printf("Passou pela my_strcdup c str = |%s| e str2 = |%s|\n", *str, str2);
		free(str2);
	}
//	printf("Passou do if da is_there_space e vai pro fromstrcdup(str, '=')\n");
	new_value = fromstrcdup(*str, '=');
	printf("Passou pela fromstrcdup(*str, '='). node = |%p|, str = |%s| e new_value = |%s|\n", node, *str, new_value);
	if (node != NULL)
		change_value(node, new_value);
	else
		create_new_ev(*str, command->my_env);
	free(end_str);
	free(new_value);
}

void	my_unset(char *name, t_command *command)
{
	t_node	*node;

	if (!name)
		return ;
	node = my_getenv_by_list(name, command->my_env);
	if (node != NULL)
		remove_node(node, command->my_env);
}
