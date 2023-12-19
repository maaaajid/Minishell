/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:06:33 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 08:18:58 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_for_pipe(char p)
{
	if (p == '|')
		return (true);
	return (false);
}

bool	check_for_redirection(char p)
{
	if (p == '<' || p == '>')
		return (true);
	return (false);
}

bool	check_for_space(char p)
{
	if (p == ' ')
		return (true);
	return (false);
}

t_env	*ft_lst_find(t_env *env, char *found)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!ft_strcmp(head->name, found))
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	ft_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
