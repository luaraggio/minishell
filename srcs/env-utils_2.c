/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:19 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/12 17:08:44 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*init_env(char **envp)
{
	t_env	env;
	t_env	*env_list;
	size_t	n;

	size = get_env_size(envp);
	env_list = (t_env *)malloc(sizeof(t_env) * size);
	if (!env_list)
		return (NULL);
	n = -1;
	while (n++ < size)
	{
// strndup or strncpy + strchr
	}
	return (env_list);
}
