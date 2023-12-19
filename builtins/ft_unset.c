/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:51:36 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/26 01:07:02 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_cd_error(t_env *tmp, int flag, char *old)
{
	if (tmp->value[0] == '\0')
	{
		if (flag == 1)
			write(2, "\n", 1);
		free(old);
	}
	else if (access(tmp->value, X_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(tmp->value, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(old);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(tmp->value, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(old);
	}
}

int	valid_of_var(char *str)
{
	int	x;

	x = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[x])
	{
		if (!ft_isalnum(str[x]) && str[x] != '_')
			return (0);
		x++;
	}
	if (!ft_isalnum(str[x - 1]) && str[x - 1] != '_')
		return (0);
	return (1);
}

void	del_node(t_env *tmp, char *cmd, t_env *last_tmp)
{
	while (tmp && ft_strcmp(tmp->name, cmd) != 0)
	{
		last_tmp = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		if (!tmp->next)
			last_tmp->next = NULL;
		else
			last_tmp->next = tmp->next;
		free(tmp);
	}
	if (!valid_of_var(cmd))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
	}
}

void	ft_unset(char **cmd, t_env **env)
{
	int		x;
	t_env	*tmp;
	t_env	*one;

	tmp = *env;
	x = 1;
	g_exit_status = 0;
	while (tmp && cmd[x])
	{
		tmp = *env;
		one = 0;
		if (ft_strcmp(tmp->name, cmd[x]) == 0)
		{
			one = tmp;
			*env = (*env)->next;
			free(one->name);
			if (one->value)
				free(one->value);
			free(one);
			x++;
			continue ;
		}
		del_node(tmp, cmd[x], one);
		x++;
	}
}
