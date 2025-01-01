/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:29:26 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/01 15:21:35 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	print_error(t_token *token)
{
	if (token->state == Q_UNCLOSE)
		write(STDERR_FILENO, "quotes (\' or \") unclose \n", 25);
	else if (token->state == RED_ERR)
		write(STDERR_FILENO, "redir (<<< or >>> or <>)\n", 25);
	else
	{
		write(STDERR_FILENO, "bash: erreur de syntaxe près ", 29);
		write(STDERR_FILENO, "du symbole inattendu « ", 25);
		write(STDERR_FILENO, token->value, ft_strlen(token->value));
		write(STDERR_FILENO, " » \n", 6);
		return ;
	}
}

int	check_red(t_token *token)
{
	t_token	*tokens;

	if (token->next)
	{
		if (token->type == OUT_REDIR && token->next->type == PIPE)
			return (OK);
	}
	tokens = token->next;
	while (tokens && tokens->type == A_SPACE)
		tokens = tokens->next;
	if (!tokens || (tokens->type != CMD
			&& tokens->type != EXIT_STATUS && tokens->type != NEW_TYPE)
		|| (!ft_strcmp(tokens->value, "") && tokens->state == NORMAL))
	{
		return (ERROR);
	}
	return (OK);
}

t_token	*ft_beffor(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp && tmp->type == A_SPACE)
		tmp = tmp->prev;
	return (tmp);
}

t_token	*ft_affter(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp && tmp->type == A_SPACE)
		tmp = tmp->next;
	return (tmp);
}
