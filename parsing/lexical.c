/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:50:07 by asmae             #+#    #+#             */
/*   Updated: 2024/12/24 13:03:10 by atahtouh         ###   ########.fr       */
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

char	*ft_slash(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	add_token(token, create_token(ft_strndup(input, 1), type, state));
	return (input + 1);
}

char	*ft_tokenisation(char *input, t_token **token)
{
	if (!ft_check_caracter(*input))
		input = ft_cmd(input, token, CMD, NORMAL);
	else if (*input == ' ')
		input = ft_space(input, token, A_SPACE, NORMAL);
	else if (*input == '|')
		input = ft_pipe(input, token, PIPE, NORMAL);
	else if (*input == '\'')
		input = ft_single_quote(input, token, CMD, IN_SQUOT);
	else if (*input == '"')
		input = ft_double_quote(input, token, CMD, IN_DQUOT);
	else if (*input == '<')
		input = ft_red_in(input, token, IN_REDIR, NORMAL);
	else if (*input == '>')
		input = ft_red_out(input, token, OUT_REDIR, NORMAL);
	else if (*input == '$')
		input = ft_dollar(input, token, ENV_VAR, NORMAL);
	else if (*input == '~')
		input = ft_home(input, token);
	else if (*input == '\\')
		input = ft_slash(input, token, SLASH, NORMAL);
	return (input);
}

t_token	*analyse_lexical(char *input, t_env **env)
{
	t_token	*token;
	char	*clear;

	token = NULL;
	clear = input;
	while (input && *input)
	{
		// printf("hello\n");
		input = ft_tokenisation(input, &token);
	}
	ft_expand(&token, env);
	// more_analyse(&token);
	analyze_tokens(&token);
	free(clear);
	return (token);
}
