/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:29:26 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/28 20:48:05 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	print_error(t_token *token)
{
	if (token->state == Q_UNCLOSE)
		write(1, "quotes (\' or \") unclose \n", 25);
	else if (token->state == RED_ERR)
		printf("redirections error\n");
	write(1, "bash: erreur de syntaxe près ", 29);
	write(1, "du symbole inattendu « newline »\n", 32);
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
	if (!tokens || (tokens->type != CMD && tokens->type != EXIT_STATUS)
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
