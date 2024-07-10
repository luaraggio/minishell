/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:45 by dherszen          #+#    #+#             */
/*   Updated: 2024/07/10 19:21:46 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h" // trocar depois para "minishell.h"

int	ft_echo(char **args)
{
	int	n;
	int	newline;

	n = 0;
	newline = 1;
	n++; // depois tirar
	n++; // depois tirar
	if (args[n] && !ft_strncmp(args[n], "-n", 2))
	{
		newline = 0;
		n++;
	}
	ft_putstr_fd(args[n], STDOUT_FILENO);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args)
{
	int	n;

	n = 0;
	n++; // depois tirar
	n++; // depois tirar
	// precisa atualizar os ENV OLDPWD?
	// erro segfault qdo digita apenas "cd"
	if ((!args[n] && chdir(getenv("HOME")) != 0)
		|| (!ft_strcmp(args[n], "~") && chdir(getenv("HOME")) != 0)) // aqui pode usar o getenv ou tem q vir do execve?
	{
		perror("minishell: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	else if (!ft_strcmp(args[n], "-"))
	{
		if (chdir(getenv("OLDPWD")) != 0)
		{
			perror("minishell: cd: OLDPWD not set\n");
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(args[n]) != 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(args[n], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	printf("Current working directory: %s\n", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}
int	ft_pwd(char **args)
{
	// pwd pode receber n argumentos mas ele ignora. Se tiver mais de um argumento, ele ignora os outros, sem erro.
	(void)args;
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

void	print_builtin(char **args)
{
	int	n;

	n = 0;
	n++; // depois tirar
	n++; // depois tirar
	while (args[n])
	{
		if (n - 2 == 0 ) // depois mudar para n == 0
			printf("Command: %s\n", args[n - 1]);
		printf("Arg %d: %s\n", n - 1, args[n]); // depois mudar para n
		n++;
	}
}

int	main(int argc, char **argv)
{
	print_builtin(argv);
	(void)argc;
	if (!ft_strncmp(argv[1], "echo", 4))
		ft_echo(argv);
	else if (!ft_strncmp(argv[1], "cd", 2))
		ft_cd(argv);
	else if (!ft_strncmp(argv[1], "pwd", 3))
		ft_pwd(argv);
	return (EXIT_SUCCESS);
}
