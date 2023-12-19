/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:31:51 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 01:03:12 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	new_pwd(t_env *env, char *name, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = str;
	}
	else if (env && !tmp && !ft_strcmp(name, "OLDPWD"))
	{
		ft_listadd_back(&env, ft_list_new("OLDPWD"));
		tmp = env;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->value = str;
	}
	else
		free(str);
	g_exit_status = 0;
}

void	go_to_home(t_env *env)
{
	t_env	*tmp;
	char	*new;
	char	*old;
	int		x;

	tmp = env;
	while (tmp && ft_strcmp("HOME", tmp->name))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		old = getcwd(0, 0);
		x = chdir(tmp->value);
		if (x == -1)
			put_cd_error(tmp, 0, old);
		else
		{
			new = getcwd(0, 0);
			tmp = env;
			new_pwd(tmp, "OLDPWD", old);
			new_pwd(tmp, "PWD", new);
		}
	}
	else
		ft_putstr_fd("cd: HOME not set\n", 2);
}

void	go_to_oldpwd(t_env *env)
{
	t_env	*tmp;
	char	*old;
	char	*new;

	tmp = env;
	g_exit_status = 1;
	while (tmp && ft_strcmp("OLDPWD", tmp->name))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		old = getcwd(0, 0);
		if (chdir(tmp->value) == -1)
			put_cd_error(tmp, 1, old);
		else
		{
			tmp = env;
			new = getcwd(0, 0);
			ft_putstr_fd(new, 1);
			new_pwd(tmp, "PWD", new);
			new_pwd(tmp, "OLDPWD", old);
			write(1, "\n", 1);
		}
	}
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
}

void	norm_cd(char *cmd, t_env **env, char *old, int flag)
{
	char	*new;

	old = getcwd(0, 0);
	flag = chdir(cmd);
	new = getcwd(0, 0);
	if (flag == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(old);
		free(new);
	}
	else if (!new)
		put_big_cd_err(old, new);
	else
	{
		new_pwd(*env, "OLDPWD", old);
		new_pwd(*env, "PWD", new);
	}
}

void	ft_cd(char **cmd, t_env *env)
{
	t_env	*tmp;
	int		flag;
	char	*old;

	tmp = env;
	old = NULL;
	flag = 0;
	g_exit_status = 1;
	if (!cmd[1] || cmd[1][0] == '~')
		go_to_home(tmp);
	else if (!ft_strcmp(cmd[1], "-"))
		go_to_oldpwd(tmp);
	else
	{
		tmp = env;
		norm_cd(cmd[1], &tmp, old, flag);
	}
}
