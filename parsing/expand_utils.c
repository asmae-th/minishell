/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:38:20 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/02 01:53:48 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	get_prev(t_token *token)
{
	t_token	*tmp;
	int		i;
	int		j;

	if (!token)
		return (0);
	i = 0;
	j = 0;
	tmp = token->prev;
	while (tmp)
	{
		if (tmp->type == A_SPACE)
			i++;
		if (tmp->type == HERE_DOC)
		{
			j = 5;
			break ;
		}
		tmp = tmp->prev;
	}
	if (i == 1 && j == 5)
		return (1);
	return (0);
}

size_t	ft_strlen1(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
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
			result = ft_strndup(tmp->val, ft_strlen1(tmp->val));
			return (result);
		}
		tmp = tmp->next;
	}
	free(value);
	return (ft_strndup("", ft_strlen("")));
}
