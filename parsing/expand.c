/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:10:23 by asmae             #+#    #+#             */
/*   Updated: 2024/12/31 12:29:27 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_token	*get_prev(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token->prev;
	while (tmp && tmp->type == A_SPACE)
	{
		tmp = tmp->prev;
	}
	return (tmp);
}

char	*ft_remplace_var(char *value, t_envp **env)
{
	t_envp	*tmp;
	char	*result;

	tmp = (*env)->next;
	while (tmp)
	{
		if (!ft_strcmp(value + 1, tmp->var))
		{
			free(value);
			result = ft_strndup(tmp->val, ft_strlen(tmp->val));
			return (result);
		}
		tmp = tmp->next;
	}
	free(value);
	return (ft_strndup("", ft_strlen("")));
}

void	ft_expand(t_token **token, t_envp **env)
{
	t_token	*tmp_token;
	t_token	*tmp_prev;

	tmp_token = *token;
	while (tmp_token)
	{
		if (tmp_token->type == ENV_VAR || tmp_token->type == SPECIAL_VAR)
		{
			if (tmp_token->prev != NULL)
			{
				tmp_prev = get_prev(tmp_token);
				if (tmp_prev->type == HERE_DOC)
				{
					tmp_token->type = CMD;
					tmp_token = tmp_token->next;
					continue ;
				}
			}
			tmp_token->value = ft_remplace_var(tmp_token->value, env);
			tmp_token->type = CMD;
		}
		tmp_token = tmp_token->next;
	}
}
