/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:17:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:18:47 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_list_find(t_env *env, char *found)
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

static void	f_exitit(int x)
{
	if (x == 0)
		return ;
	printf("[%d]", x);
}

static void	check_for_path(t_env *env)
{
	char	*ptr;
	char	*pwd;
	int		len;
	t_env	*newhome;

	pwd = getcwd(NULL, 4096);
	newhome = ft_list_find(env, "HOME");
	if (newhome && ft_strlen(newhome->value) > 0)
	{
		len = ft_strlen(newhome->value);
		if (ft_strncmp(pwd, newhome->value, len) == 0)
		{
			ptr = ft_substr(pwd, len, ft_strlen(pwd) - len);
			printf("[~%s]", ptr);
			free(pwd);
			free(ptr);
			return ;
		}
	}
	printf("[%s]", pwd);
	free(pwd);
}

static void	check_fo_user(t_env *env)
{
	t_env		*ptr;

	ptr = ft_list_find(env, "USER");
	if (!ptr)
		return ;
	if (ptr->value)
		printf("%s@", ptr->value);
}

void	my_prompt(t_env *env)
{
	check_fo_user(env);
	check_for_path(env);
	f_exitit(g_exit_status);
	printf("\n");
}
