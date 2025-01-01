/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:50:07 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 10:19:52 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*ft_slash(char *input, t_token **token,
		t_token_type type, t_token_state state)
{
	if (*input && *(input + 1))
	{
		add_token(token, create_token(ft_strndup(input, 1), type, state));
		add_token(token, create_token(ft_strndup(input + 1, 1), CMD, state));
		return (input + 2);
	}
	else
	{
		add_token(token, create_token(ft_strndup(input, 1), type, state));
		return (input + 1);
	}
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

t_token	*analyse_lexical(char *input, t_envp **env)
{
	t_token	*token;
	char	*clear;

	token = NULL;
	clear = input;
	while (input && *input)
	{
		input = ft_tokenisation(input, &token);
	}
	ft_expand(&token, env);
	more_analyse(&token);
	// t_token *tmp = token;
	// while (tmp)
	// {
	// 	printf("value : %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
	free(clear);
	return (token);
}
