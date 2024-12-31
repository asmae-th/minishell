/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:10:33 by asmae             #+#    #+#             */
/*   Updated: 2024/12/31 11:29:06 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	extract_squot_content(char *input)
{
	int	j;

	j = 0;
	while (input[j] && input[j] != '\'')
	{
		if (input[j + 1] == '\'' && input[j + 2] == '\'')
			j += 2;
		j++;
	}
	return (j);
}

char	*ft_single_quote(char *input, t_token **token,
		enum e_token_type t_type, enum e_token_state s_token)
{
	int	j;

	input++;
	j = extract_squot_content(input);
	if (input[j] == 0 || !(*input))
	{
		t_type = SYNTAX_ERROR;
		s_token = Q_UNCLOSE;
		if (*input == input[j])
		{
			add_token(token,
				create_token(ft_strndup("SQUOTE_ERROR",
						ft_strlen("SQUOTE_ERROR")), t_type, s_token));
			return (input + j);
		}
	}
	add_token(token, create_token(ft_strndup(input, j),
			t_type, s_token));
	if (input[j] == '\'')
		j++;
	return (input + j);
}

int	content_quote(char **input, t_token **token,
	t_token_type type, t_token_state state)
{
	int	i;

	i = 0;
	while ((*input)[i] && (*input)[i] != '"')
	{
		if ((*input)[i] == '\\' && (*input)[i + 1] == '$')
		{
			i += 2;
			input = input + 1;
		}
		else if ((*input)[i] == '$')
		{
			if (i)
				add_token(token, create_token(ft_strndup((*input), i),
						type, state));
			(*input) = ft_dollar((*input) + i, token, ENV_VAR, state);
			i = 0;
		}
		else
			i = handle_other_cases(input, i);
	}
	return (i);
}

char	*ft_double_quote(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	int	i;

	input++;
	i = content_quote(&input, token, type, state);
	if (input[i] == 0 || !(*input))
	{
		type = SYNTAX_ERROR;
		state = Q_UNCLOSE;
		if (*input == input[i])
		{
			add_token(token, create_token(ft_strndup("DQUOTE_ERROR",
						ft_strlen("DQUOTE_ERROR")), type, state));
			return (input + i);
		}
	}
	add_token(token, create_token(ft_strndup(input, i), type, state));
	if (input[i] == '"')
		i++;
	return (input + i);
}

char	*ft_dollar(char *input, t_token **token,
	t_token_type t_type, t_token_state s_token)
{
	int	i;

	i = 0;
	if (*(input + 1) && (ft_isdigit(*(input + 1))
			|| *(input + 1) == '?' || *(input + 1) == '$'))
	{
		t_type = type_is(*(input + 1));
		add_token(token, create_token(ft_strndup(input, 2),
				t_type, s_token));
		return (input + 2);
	}
	i = var_extracter(input, i);
	if (!i)
		t_type = CMD;
	if (i)
		add_token(token,
			create_token(ft_strndup(input, i + 1), t_type, s_token));
	else
	{
		i = set_i(input, i);
		add_token(token,
			create_token(ft_strndup(input, i + 1), t_type, s_token));
	}
	return (input + i + 1);
}
