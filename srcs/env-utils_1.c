/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:36:56 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/12 18:04:46 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

size_t	get_env_size(char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

t_env	*new_env(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env) * 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_env(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
