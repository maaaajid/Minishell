/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:43 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 07:25:38 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*remove_them(char *token, int *i)
{
	char	q;
	int		j;
	char	*temp[2];
	char	*n_tok;

	q = token[*i];
	j = *i + 1;
	while (token[j] && token[j] != q)
		j++;
	temp[0] = ft_substr(token, 0, *i);
	temp[1] = ft_substr(token, *i + 1, j - *i - 1);
	n_tok = ft_strjoin(temp[0], temp[1]);
	free (temp[0]);
	free (temp[1]);
	*i = j - 2;
	temp[0] = ft_strjoin(n_tok, token + j + 1);
	free (token);
	free (n_tok);
	token = ft_strdup(temp[0]);
	free (temp[0]);
	return (token);
}

static char	*remove_token_quotes(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
			token = remove_them(token, &i);
		i++;
	}
	return (token);
}

void	del_quotes(char **com)
{
	int	i;

	i = 0;
	while (com[i])
	{
		if (((com[i] && ft_strchr(com[i], '\''))
				|| (com[i] && ft_strchr(com[i], '"'))))
			com[i] = remove_token_quotes(com[i]);
		i++;
	}
}
