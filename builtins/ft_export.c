/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:45:58 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/26 02:19:24 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	i_of_ecoul(char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	while (str[x])
	{
		if (str[x] == '=' || str[x] == '+')
		{
			if (str[x] == '=')
				return (x);
			if (str[x] == '+' && str[x + 1] == '=')
				return (x);
		}
		x++;
	}
	return (x);
}

int	check_valid_var(char *str)
{
	int	x;

	x = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[x] && str[x] != '+' && str[x] != '=')
	{
		if (!ft_isalnum(str[x]) && str[x] != '_')
			return (0);
		x++;
	}
	if (str[x] != '\0')
	{
		if (str[x] == '=')
			return (1);
		if (str[x] == '+' && str[x + 1] != '=' )
			return (0);
	}
	if (!ft_isalnum(str[x - 1]) && str[x - 1] != '_')
		return (0);
	return (1);
}

void	not_exist(char *cmd, t_env **env)
{
	char	*key;

	key = ft_substr(cmd, 0, i_of_ecoul(cmd) + 2);
	if (check_valid_var(key))
	{
		ft_listadd_back(env, ft_list_new(cmd));
	}
	else
	{
		ft_putstr_fd("export: `", 2);
		if (ft_strchr(cmd, '='))
		{
			free(key);
			key = ft_substr(cmd, 0, i_of_ecoul(cmd));
			ft_putstr_fd(key, 2);
		}
		else
			ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
	}
	free(key);
}

void	export_put(char *cmd, t_env *tmp, t_env **env)
{
	char	*join;
	char	*str;

	if (tmp)
	{
		if (cmd[i_of_ecoul(cmd)] == '+' && tmp->value)
		{
			str = ft_strchr(cmd, '=') + 1;
			join = ft_strjoin(tmp->value, str);
			if (tmp->value)
				free(tmp->value);
			tmp->value = join;
		}
		else if (ft_strchr(cmd, '='))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(ft_strchr(cmd, '=') + 1);
		}
	}
	else if (!tmp)
		not_exist(cmd, env);
}

void	ft_export(char **cmd, t_env **env)
{
	int		x;
	t_env	*tmp;
	char	*key;

	x = 0;
	g_exit_status = 0;
	tmp = *env;
	if (two_d_len(cmd) == 1)
		export_print(tmp);
	else if (two_d_len(cmd) > 1)
	{
		while (cmd[++x])
		{
			tmp = *env;
			key = ft_substr(cmd[x], 0, i_of_ecoul(cmd[x]));
			while (tmp && ft_strcmp(tmp->name, key) != 0)
			{
				tmp = tmp->next;
				if (!tmp)
					break ;
			}
			free(key);
			export_put(cmd[x], tmp, env);
		}
	}
}
