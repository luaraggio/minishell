/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:43:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 22:19:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *str)
{
	my_putstr_fd(str, 2);
}

void	print_no_such_file(char **argv)
{
	print_error("bash: ");
	print_error(argv[1]);
	print_error(": No such file or directory\n");
}
