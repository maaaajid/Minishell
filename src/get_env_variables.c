/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:24:28 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 08:17:10 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_listadd_back(t_env **env, t_env *tmp)
{
	t_env	*p;

	if (!tmp || !env)
		return ;
	if (*env == NULL)
		*env = tmp;
	else
	{
		p = ft_list_last(*env);
		p->next = tmp;
		tmp->prev = p;
	}
}

void	op_put(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->name, str))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_listadd_back(env, ft_list_new(str));
	}
}

static void	add_and_initialize(char *str, t_env **temp)
{
	int	size;
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	if (str[i - 1] == '+')
	{
		(*temp)->name = ft_calloc(sizeof(char), i);
		ft_strlcpy((*temp)->name, str, i);
	}
	else
	{
		(*temp)->name = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy((*temp)->name, str, i + 1);
	}
	size = ft_strlen(str) - ft_strlen((*temp)->name);
	(*temp)->value = ft_calloc(sizeof(char), size);
	ft_strlcpy((*temp)->value, str + i + 1, size);
}

t_env	*ft_list_new(char *str)
{
	t_env	*tmp;

	tmp = ft_calloc(sizeof(t_env), 1);
	if (!tmp)
		return (0);
	if (!ft_strchr(str, '='))
	{
		tmp->name = ft_strdup(str);
		if (!tmp->name)
			return (0);
		tmp->value = NULL;
	}
	else
		add_and_initialize(str, &tmp);
	return (tmp);
}

t_env	*envp_var(char **env)
{
	t_env	*ptr;
	t_env	*rot;
	int		i;

	i = 0;
	rot = NULL;
	while (env[i])
	{
		ptr = ft_list_new(env[i]);
		ft_listadd_back(&rot, ptr);
		i++;
	}
	op_put(&rot, "OLDPWD");
	return (rot);
}
