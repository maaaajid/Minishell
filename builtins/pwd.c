/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:28:26 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/26 01:12:59 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	two_d_len(char **str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_pwd(t_env *env)
{
	char	*pwd;
	t_env	*tmp;

	tmp = env;
	g_exit_status = 0;
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		while (tmp && ft_strcmp(tmp->name, "PWD"))
			tmp = tmp->next;
		if (tmp && tmp->value)
		{
			ft_putstr_fd(tmp->value, 1);
			write (1, "\n", 1);
		}
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
