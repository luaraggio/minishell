/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:31:08 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/21 14:39:33 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_echo(t_node *node)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (node->value[size])
		size++;
	while (node->value[i])
	{
		printf("%s", node->value[i]);
		if (i < (size - 1))
			printf(" ");
		i++;
	}
	printf("\n");
	return (NO_ERROR);
}
