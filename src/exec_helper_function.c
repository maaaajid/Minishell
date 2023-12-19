/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:58:19 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:21:10 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_to_array(t_env *env)
{
	int		i;
	char	**arr;
	char	*tmp;

	arr = malloc(sizeof(char *) * (ft_list_size(env) + 1));
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->name, "=");
			arr[i] = ft_strjoin(tmp, env->value);
			free (tmp);
		}
		else
			arr[i] = ft_strdup(env->name);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	last_command_sts(t_command *cmd, int i, char *p, char **toks)
{
	if (!p && !check_for_builtin(cmd->command_segments[i], cmd->token_types[i])
		&& toks)
		g_exit_status = 127;
	if (cmd->pipeline[i % 2][1] == -1
		|| cmd->pipeline[(i + 1) % 2][0] == -1)
		g_exit_status = 1;
	ft_free((void **)toks);
	free(p);
}
