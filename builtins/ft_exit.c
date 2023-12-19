/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:56:31 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/25 22:22:12 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_max_min(char *str)
{
	int	x;

	x = 0;
	while (str[x] == ' ')
		x++;
	if (ft_strlen(str) > 20)
		return (0);
	else if (str[x] == '-' && ft_strlen(str) == 20)
	{
		if (ft_strcmp(str, "-9223372036854775808") > 0)
			return (0);
	}
	else if (str[x] == '+' && ft_strlen(str) == 20)
	{
		if (ft_strncmp(str, "+9223372036854775807", 20) > 0)
			return (0);
	}
	else if (ft_strlen(str) > 19)
		return (0);
	else if (ft_isdigit(str[x]) && ft_strlen(str) == 19
		&& ft_strcmp(str, "9223372036854775807") > 0)
		return (0);
	return (1);
}

int	valid_arg(char *cmd)
{
	int	x;

	x = 0;
	while (cmd[x] == ' ')
		x++;
	if (ft_strlen(cmd) == 1 && !ft_isdigit(cmd[0]))
		return (0);
	else if (!ft_isdigit(cmd[x]))
	{
		if (cmd[x] != '+' && cmd[x] != '-')
			return (0);
		x++;
	}
	while (cmd[x])
	{
		if (!ft_isdigit(cmd[x]))
			return (0);
		x++;
	}
	if (check_max_min(cmd) == 0)
		return (0);
	return (1);
}

void	put_exit_error(char **cmd, int x)
{
	if (x >= 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!valid_arg(cmd[x]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument repuired\n", 2);
		exit (255);
	}
}

void	ft_exit(char **cmd)
{
	int	x;

	x = 1;
	while (cmd[x])
	{
		put_exit_error(cmd, x);
		if (x == 2)
			return ;
		x++;
	}
	if (cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit (ft_atoi(cmd[1]));
	}
	ft_putstr_fd("exit\n", 1);
	exit (0);
}
