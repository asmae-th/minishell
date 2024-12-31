/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:10:20 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/30 21:54:57 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	true_state(t_token *current)
{
	return (current->type != EXIT_STATUS
		&& (current->state == IN_SQUOT
			|| current->state == IN_DQUOT || current->type == CMD));
}

int	affect_index(t_token **token)
{
	t_token	*cursur;
	int		node_member;

	node_member = 0;
	cursur = (*token);
	while (cursur)
	{
		cursur->index = node_member;
		node_member++;
		cursur = cursur->next;
	}
	return (node_member);
}

void	init_holder(t_position **holder, t_token **tokens)
{
	if (*holder == NULL)
		return ;
	(*holder)->start = 0;
	(*holder)->end = 0;
	(*holder)->flag = 0;
	(*holder)->node_member = affect_index(tokens);
}

t_position	*index_getter(t_token **tokens)
{
	t_position	*holder;
	t_token		*current;

	current = (*tokens);
	holder = (t_position *)malloc(sizeof(t_position));
	init_holder(&holder, tokens);
	while (current && current->next)
	{
		while (current && current->next && current->index < holder->node_member
			&& true_state(current) && true_state(current->next))
		{
			if (holder->flag == 0)
				holder->start = current->index;
			holder->flag = 1;
			current = current->next;
		}
		if (holder->flag)
		{
			holder->end = current->index;
			return (holder);
		}
		current = current->next;
	}
	return (holder);
}

void	free_region(t_token **start, t_token **end)
{
	t_token	*current;
	t_token	*next;

	current = *start;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
		if (current == (*end))
		{
			free(current->value);
			free(current);
			break ;
		}
	}
}
