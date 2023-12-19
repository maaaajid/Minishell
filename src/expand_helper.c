/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 08:04:04 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/25 09:18:55 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	status(void)
{
	int	check;

	check = dup(0);
	if (check == -1)
		return (0);
	close(check);
	return (1);
}

t_env	*ft_list_last(t_env *env)
{
	t_env	*last;

	last = env;
	if (env == NULL)
		return (NULL);
	while (env)
	{
		last = env;
		env = env->next;
	}
	return (last);
}

char	*change_unknown_var(char *arg, int *i)
{
	char	*temp;
	char	*new_arg;

	temp = ft_substr(arg, *i + 2, ft_strlen(arg) - *i - 2);
	new_arg = ft_strjoin_char(ft_substr(arg, 0, *i), temp, ' ');
	free(arg);
	free(temp);
	*i = ft_strlen(new_arg);
	return (new_arg);
}

char	*create_new_string(char *ptr, char *arg, int last_end)
{
	char	*temp;
	char	*new_arg;

	temp = ft_substr(arg, last_end, 1000);
	free(arg);
	new_arg = ft_strjoin(ptr, temp);
	free(temp);
	return (new_arg);
}
