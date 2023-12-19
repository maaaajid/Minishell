/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:49:11 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/26 01:00:56 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_error_put(char *cmd)
{
	ft_putstr("env: ", 2);
	ft_putstr(cmd, 2);
	ft_putstr(": ", 2);
	if (access(cmd, X_OK))
	{
		perror("");
		g_exit_status = 127;
	}
	else
	{
		ft_putstr("permission denied\n", 2);
		g_exit_status = 126;
	}
}

void	export_print(t_env *tmp)
{
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\"', 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	ft_env(char **cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	g_exit_status = 0;
	if (two_d_len(cmd) > 1)
		env_error_put(cmd[1]);
	else
	{
		while (tmp)
		{
			if (tmp->name && tmp->value)
			{
				ft_putstr_fd(tmp->name, 1);
				write (1, "=", 1);
				ft_putstr_fd(tmp->value, 1);
				write (1, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
}
