/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:11:50 by asmae             #+#    #+#             */
/*   Updated: 2024/12/31 14:19:09 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	redir_case(enum e_token_type type)
{
	if (type == IN_REDIR || type == OUT_REDIR || type == APPEND
		|| type == HERE_DOC)
		return (1);
	else
		return (0);
}

int	is_outred(t_token *behind, t_token *forward)
{
	if (behind->type == OUT_REDIR)
	{
		if (behind->next->type == PIPE && !redir_case(forward->type))
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	return (0);
}

int	check_pipe(t_token *token)
{
	t_token	*beffor;
	t_token	*affter;

	beffor = ft_beffor(token);
	affter = ft_affter(token);
	if (!beffor || !affter
		|| (beffor->type != CMD && beffor->type != EXIT_STATUS
			&& is_outred(beffor, affter))
		|| (affter->type != CMD && affter->type != EXIT_STATUS
			&& !redir_case(affter->type)))
	{
		return (ERROR);
	}
	return (OK);
}

int	ft_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		return (print_error(tmp), ERROR);
	while (tmp)
	{
		if (tmp->type == SYNTAX_ERROR)
			return (print_error(tmp), ERROR);
		if (tmp->type == OUT_REDIR || tmp->type == IN_REDIR
			|| tmp->type == APPEND || tmp->type == HERE_DOC)
		{
			if (check_red(tmp) == ERROR)
				return (print_error(tmp), ERROR);
		}
		if (tmp->type == PIPE)
		{
			if (check_pipe(tmp) == ERROR)
				return (print_error(tmp), ERROR);
		}
		tmp = tmp->next;
	}
	return (OK);
}

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
