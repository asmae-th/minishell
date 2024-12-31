/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_analyse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:00:09 by asmae             #+#    #+#             */
/*   Updated: 2024/12/30 21:32:03 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token	*data_assembler(t_token **tokens, t_position *position)
{
	t_token	*cursur;
	t_token	*new_node;

	cursur = (*tokens);
	while (cursur)
	{
		if (cursur->index == position->start)
		{
			new_node = create_token(assemble_data(cursur,
						position->end), CMD, NORMAL);
			new_node->index = position->start;
			new_node->prev = cursur->prev;
		}
		if (cursur->index == position->end)
			new_node->next = cursur->next;
		cursur = cursur->next;
	}
	return (new_node);
}

void	addclean_token(t_token **head, int start_index,
			int end_index, t_token *clean_node)
{
	t_token	*start;
	t_token	*end;
	int		i;

	start = *head;
	end = *head;
	i = -1;
	while (++i < start_index && start != NULL)
		start = start->next;
	i = -1;
	while (++i < end_index && end != NULL)
		end = end->next;
	if (start->prev == NULL)
		*head = clean_node;
	else
		start->prev->next = clean_node;
	if (end->next != NULL)
		end->next->prev = clean_node;
	clean_node->prev = start->prev;
	clean_node->next = end->next;
	free_region(&start, &end);
}

void	ft_clean(t_token **tokens)
{
	t_token		*cursur;
	t_position	*to_extract;

	cursur = (*tokens);
	while (cursur)
	{
		to_extract = index_getter(tokens);
		if (to_extract->start != to_extract->end)
		{
			addclean_token(tokens, to_extract->start, to_extract->end,
				data_assembler(tokens, to_extract));
			cursur = (*tokens);
		}
		cursur = cursur->next;
		free(to_extract);
	}
}

void	more_analyse(t_token **token)
{
	t_token	*current;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		if (search_quote(current->value)
			&& (current->state == IN_DQUOT || current->state == IN_SQUOT))
		{
			current->value = supr_quote(current->value, current->state);
			current->state = NORMAL;
		}
		current = current->next;
	}
	ft_clean(token);
}
