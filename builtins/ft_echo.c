/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:36 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/26 01:03:46 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_big_cd_err(char *old, char *new)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	free(old);
	free(new);
	g_exit_status = 1;
}

int	check_for_n(char *cmd)
{
	int	x;

	x = 1;
	if (!cmd)
		return (0);
	if (ft_strlen(cmd) < 2)
		return (0);
	while (cmd[x])
	{
		if (cmd[0] != '-')
			return (0);
		if (cmd[x] != 'n')
			return (0);
		x++;
	}
	return (1);
}

void	ft_echo(char **cmd, int *tok)
{
	int	x;
	int	z;

	z = 0;
	x = 1;
	(void)tok;
	g_exit_status = 0;
	if (cmd[x] && ft_strncmp(cmd[x], "-n", 2) == 0)
	{
		while (check_for_n(cmd[x]))
		{
			z = 1;
			x++;
		}
	}
	while (cmd[x])
	{
		ft_putstr_fd(cmd[x], 1);
		if (cmd[x + 1] != NULL)
			write (1, " ", 1);
		x++;
	}
	if (z == 0)
		write (1, "\n", 1);
}
