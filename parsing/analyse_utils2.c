/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:14:52 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 14:19:21 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc(len_s1 + len_s2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < len_s1)
		join[i] = s1[i];
	while (++j < len_s2)
		join[i + j] = s2[j];
	join[i + j] = '\0';
	free(s1);
	return (join);
}

char	*assemble_data(t_token *begin, int end)
{
	char	*join;

	join = ft_strndup(begin->value, (int)ft_strlen(begin->value));
	while (begin->index < end)
	{
		join = ft_strjoin1(join, begin->next->value);
		begin = begin->next;
	}
	return (join);
}
