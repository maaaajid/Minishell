/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:04:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 05:04:39 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**split_path(t_env *env)
{
	t_env	*ptr;
	char	**path;

	ptr = env;
	while (ptr && ft_strcmp(ptr->name, "PATH"))
		ptr = ptr->next;
	path = NULL;
	if (ptr)
		path = ft_split(ptr->value, ':');
	return (path);
}

static char	*getpath(int axcess, char *cmd, char **spl_p, int i)
{
	char	*com_path;

	if (!axcess)
		return (ft_strdup(cmd));
	if (!spl_p)
	{
		perror(cmd);
		return (NULL);
	}
	cmd = ft_strjoin("/", cmd);
	while (spl_p && spl_p[i] && axcess == -1)
	{
		com_path = ft_strjoin(spl_p[i++], cmd);
		axcess = access(com_path, X_OK);
		if (axcess == -1)
			free(com_path);
	}
	free(cmd);
	if (axcess == -1)
		return (NULL);
	return (com_path);
}

int	ft_is_folder_or_file(char **arg)
{
	struct stat	filestat;

	lstat(arg[0], &filestat);
	if (S_ISDIR(filestat.st_mode))
	{
		ft_printf(2, "%s: is a directory\n", arg[0]);
		return (126);
	}
	else
	{
		if (access(arg[0], F_OK))
		{
			ft_printf(2, "%s: No such file or directory\n", arg[0]);
			return (127);
		}
		else if (!access(arg[0], F_OK) && (access(arg[0], X_OK)
				|| access(arg[0], R_OK)))
		{
			ft_printf(2, "%s: Permission denied\n", arg[0]);
			return (126);
		}
		return (0);
	}
}

int	ft_includeback_s(char *arg)
{
	int	j;

	j = 0;
	while (arg && arg[j])
	{
		if (arg[j] == '/')
			return (1);
		j++;
	}
	return (0);
}

char	*get_thepath(char **args, int *toks, t_env *env)
{
	int		i;
	char	**path;
	int		axcess;
	char	*cmd;

	i = 0;
	while (args[i] && toks[i] != COM_NAME && toks[i] != COM_ARGUMENT)
		i++;
	if (!args[i] || !args[i][0])
		return (NULL);
	if (ft_includeback_s(args[0]))
	{
		g_exit_status = ft_is_folder_or_file(args);
		if (g_exit_status)
			return (NULL);
	}
	else if (access(args[0], X_OK) == 0)
		return (ft_printf(2, "%s: command not found\n", args[0]),
			g_exit_status = 127, (NULL));
	path = split_path(env);
	axcess = access(args[i], X_OK);
	cmd = getpath(axcess, args[i], path, 0);
	ft_free((void **)path);
	return (cmd);
}
