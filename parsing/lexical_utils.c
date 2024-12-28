/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:00:46 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/28 20:02:26 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_check_caracter(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '|' || c == '\\'
		|| c == '$' || c == '<' || c == '>' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char	*ft_strndup(char *str, int n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((n + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (str[i] && i < n)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_cmd(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	int	i;

	i = 0;
	while (input[i] && !ft_check_caracter(input[i]))
		i++;
	add_token(token, create_token(ft_strndup(input, i), type, state));
	return (input + i);
}

char	*ft_space(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	add_token(token, create_token(ft_strndup(input, 1), type, state));
	return (input + 1);
}

char	*ft_pipe(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	add_token(token, create_token(ft_strndup(input, 1), type, state));
	return (input + 1);
}
