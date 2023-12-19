/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 07:25:46 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:23:45 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*exit_status_state(char *arg, int *i)
{
	int		len;
	char	*temp;
	char	*itoa_exitcode;
	char	*sub;
	char	*new_arg;

	len = ft_strlen(arg);
	temp = ft_substr(arg, *i + 2, len - (*i + 2));
	itoa_exitcode = ft_itoa(g_exit_status);
	sub = ft_substr(arg, 0, *i);
	new_arg = ft_strjoin_many(3, sub, itoa_exitcode, temp);
	free(arg);
	free(sub);
	free(temp);
	free(itoa_exitcode);
	*i = ft_strlen(new_arg);
	return (new_arg);
}

static char	*change_and_replace(char *arg, int *i, t_env *env, char *ptr)
{
	int		last_end;
	char	*name;
	char	*temp;
	t_env	*cur;
	char	*new_arg;

	last_end = (*i) + 1;
	while ((arg[last_end] && ft_isalnum(arg[last_end]))
		|| (arg[last_end] && arg[last_end] == '_'))
		last_end++;
	name = ft_substr(arg, (*i) + 1, last_end - (*i) - 1);
	cur = ft_lst_find(env, name);
	temp = ft_substr(arg, 0, *i);
	if (cur && cur->value)
		ptr = ft_strjoin(temp, cur->value);
	else
		ptr = ft_strjoin(temp, "");
	free(temp);
	new_arg = create_new_string(ptr, arg, last_end);
	*i = ft_strlen(ptr);
	free(ptr);
	free(name);
	return (new_arg);
}

static char	*replace_them(char *arg, int *i, t_env *env, int st)
{
	char	*ptr;

	ptr = NULL;
	if ((arg[*i] == '$' && st != 1 && ft_isalpha(arg[*i + 1]))
		|| (arg[*i] == '$' && st != 1 && arg[*i + 1] == '_'))
	{
		arg = change_and_replace(arg, i, env, ptr);
		if (arg[*i] == '$' || arg[*i] == '"' || arg[*i] == '\'')
			*i -= 1;
		else if (arg[*i] == 0)
			*i = -2;
	}
	else if (arg[*i] == '$' && st != 1)
	{
		arg = change_unknown_var(arg, i);
		if (arg[*i] == '$' || arg[*i] == '"' || arg[*i] == '\'')
			*i -= 1;
		else if (arg[*i] == 0)
			*i = -2;
	}
	return (arg);
}

static char	*after_dollar(char *arg, t_env *env)
{
	int	i;
	int	st;

	i = 0;
	st = 0;
	while (i != -1 && arg[i])
	{
		change_value_state(&st, arg[i]);
		if (arg[i] == '$' && st != 1 && arg[i + 1] == '?')
		{
			arg = exit_status_state(arg, &i);
			if (arg[i] == '$' || arg[i] == '"' || arg[i] == '\'')
				continue ;
			else if (arg[i] == 0)
				break ;
		}
		else if (arg[i] == '$' && st != 1 && (arg[i + 1] == ' '
				|| arg[i + 1] == '\'' || arg[i + 1] == '"' || arg[i + 1] == '$'
				|| !arg[i + 1]))
		;
		else
			arg = replace_them(arg, &i, env, st);
		i++;
	}
	return (arg);
}

void	expand_env(char **com, int *toks, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (com[i])
	{
		if (!ft_strcmp(com[i], "|"))
			g_exit_status = 0;
		if (ft_strchr(com[i], '$'))
			com[i] = after_dollar(com[i], env);
		j = 0;
		while (com[i][j])
			if (com[i][j] != ' ' || !(com[i][j] >= 9 && com[i][j] <= 13))
				break ;
		if (!com[i][j])
			toks[i] = NULL_TOKEN;
		i++;
	}
}
