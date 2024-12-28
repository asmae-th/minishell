/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:14:52 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/28 20:15:29 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	search_quote(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	len_value(char *value, t_token_state state)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (state == IN_DQUOT)
	{
		while (value[i])
		{
			if (value[i] != '\"')
				len++;
			i++;
		}
	}
	else if (state == IN_SQUOT)
	{
		while (value[i])
		{
			if (value[i] != '\'')
				len++;
			i++;
		}
	}
	return (len);
}

void	remove_double_quotes(const char *value, char *ptr, int *j)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] != '\"')
		{
			ptr[*j] = value[i];
			(*j)++;
		}
		i++;
	}
}

char	*supr_quote(char *value, t_token_state state)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = (char *)malloc((len_value(value, state) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	if (state == IN_DQUOT)
		remove_double_quotes(value, ptr, &j);
	else if (state == IN_SQUOT)
	{
		while (value[i])
		{
			if (value[i] != '\'')
			{
				ptr[j] = value[i];
				j++;
			}
			i++;
		}
	}
	ptr[j] = '\0';
	return (free(value), ptr);
}

char	*assemble_data(t_token *begin, int end)
{
	char	*join;

	join = ft_strndup(begin->value, (int)ft_strlen(begin->value));
	while (begin->index < end)
	{
		join = ft_strjoin(join, begin->next->value);
		begin = begin->next;
	}
	return (join);
}
