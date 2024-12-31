/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:08:39 by asmae             #+#    #+#             */
/*   Updated: 2024/12/30 21:23:09 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token	*create_token(char *val, t_token_type type, t_token_state state)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = val;
	new_token->type = type;
	new_token->state = state;
	new_token->index = 0;
	new_token->node_member = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (new_token->state == IN_DQUOT || new_token->state == IN_SQUOT)
		new_token->valid = TRUE;
	else
		new_token->valid = FALS;
	return (new_token);
}

void	add_token(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token)
		return ;
	if (!*token)
		*token = new_token;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

void	ft_free_token(t_token **token)
{
	t_token	*tmp;
	t_token	*current;

	current = *token;
	if (!token || !*token)
		return ;
	while (current)
	{
		tmp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	*token = NULL;
}
