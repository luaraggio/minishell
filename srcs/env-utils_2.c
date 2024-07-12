/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:19 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/12 18:05:32 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env_key(char *env)
{
	char	*key;

	key = ft_strndup(env, ft_strchr(env, '=') - env);
	return (key);
}

char	*get_env_value(char *env)
{
	char	*value;

	value = ft_strdup(ft_strchr(env, '=') + 1);
	return (value);
}

void	init_env(char **envp, t_env **env_list)
{
	size_t	n;

	size = get_env_size(envp);
	env_list = (t_env **)malloc(sizeof(t_env *) * size);
	if (!env_list)
		return (NULL);
	n = -1;
	while (n++ < size)
	{
		env_list[n] = new_env(get_env_key(envp[n]), get_env_value(envp[n]));
		if (!env_list[n])
		{
			// free previous nodes, if exists
			return (NULL);
		}
		add_env(env_list, env_list[n]);
	}
	return (env_list);
}
