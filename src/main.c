/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:07:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 00:35:26 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status;

t_token	*parse_quotes(char *line)
{
	t_norm	norm;
	t_token	*head;
	t_token	*tail;

	head = NULL;
	tail = NULL;
	norm.i = 0;
	norm.start = -1;
	norm.quote = '\0';
	while (line[norm.i])
	{
		norm_helper(line, &norm, &head, &tail);
		norm.i++;
		if (norm.quote == '\0' && (line[norm.i] == '\''
				|| line[norm.i] == '\"'))
		{
			norm.quote = line[norm.i];
			norm.start = norm.i + 1;
			norm.i++;
		}
	}
	if (norm.start >= 0)
		last_one(line, &norm, &head, &tail);
	return (head);
}

void	free_token(t_token *t)
{
	if (!t)
		return ;
	free_token(t->next);
	free(t->value);
	free(t);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env_list;
	t_token	*tokens;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	env_list = envp_var(envp);
	ft_signals(DEF_SEGNAL);
	my_prompt(env_list);
	while (42)
	{
		line = readline("MINI$ ");
		if (!line)
			return (0);
		tokens = breakdown_line(line);
		if (tokens)
		{
			add_history(line);
			command_initial(line, &env_list);
		}
		free_token(tokens);
		free(line);
		tokens = NULL;
	}
}
