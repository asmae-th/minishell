/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_analyse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:00:09 by asmae             #+#    #+#             */
/*   Updated: 2024/12/24 11:37:07 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

// int	search_quote(char *value)
// {
// 	int	i;

// 	i = 0;
// 	if (!value)
// 		return (0);
// 	while (value[i])
// 	{
// 		if (value[i] == '\"' || value[i] == '\'')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	len_value(char *value, t_token_state state)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	if (state == IN_DQUOT)
// 	{
// 		while (value[i])
// 		{
// 			if (value[i] != '\"')
// 				len++;
// 			i++;
// 		}
// 	}
// 	else if (state == IN_SQUOT)
// 	{
// 		while (value[i])
// 		{
// 			if (value[i] != '\'')
// 				len++;
// 			i++;
// 		}
// 	}
// 	return (len);
// }

// char	*supr_quote(char *value, t_token_state state)
// {
// 	int		i;
// 	int		j;
// 	char	*ptr;

// 	ptr = (char *)malloc((len_value(value, state) + 1) * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	if (state == IN_DQUOT)
// 	{
// 		while (value[i])
// 		{
// 			if (value[i] != '\"')
// 			{
// 				ptr[j] = value[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// 	else if (state == IN_SQUOT)
// 	{
// 		while (value[i])
// 		{
// 			if (value[i] != '\'')
// 			{
// 				ptr[j] = value[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// 	ptr[j] = '\0';
// 	free(value);
// 	return (ptr);
// }

// char	*assemble_data(t_token *begin, int end)
// {
// 	char	*join;

// 	join = ft_strndup(begin->value, (int)ft_strlen(begin->value));
// 	while (begin->index < end)
// 	{
// 		join = ft_strjoin(join, begin->next->value);
// 		begin = begin->next;
// 	}
// 	return (join);
// }

// t_token	*data_assembler(t_token **tokens, t_position *position)
// {
// 	t_token	*cursur;
// 	t_token	*new_node;

// 	cursur = (*tokens);
// 	while (cursur)
// 	{
// 		if (cursur->index == position->start)
// 		{
// 			new_node = create_token(assemble_data(cursur,
// 						position->end), CMD, NORMAL);
// 			new_node->index = position->start;
// 			new_node->prev = cursur->prev;
// 		}
// 		if (cursur->index == position->end)
// 			new_node->next = cursur->next;
// 		cursur = cursur->next;
// 	}
// 	return (new_node);
// }

// void	free_region(t_token **start, t_token **end)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = *start;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->value);
// 		free(current);
// 		current = next;
// 		if (current == (*end))
// 		{
// 			free(current->value);
// 			free(current);
// 			break ;
// 		}
// 	}
// }

// int	true_state(t_token *current)
// {
// 	return (current->type != EXIT_STATUS && \
// 		(current->state == IN_SQUOT || \
// 		current->state == IN_DQUOT || current->type == CMD));
// }

// int	affect_index(t_token **token)
// {
// 	t_token	*cursur;
// 	int		node_member;

// 	node_member = 0;
// 	cursur = (*token);
// 	while (cursur)
// 	{
// 		cursur->index = node_member;
// 		node_member++;
// 		cursur = cursur->next;
// 	}
// 	return (node_member);
// }

// void	init_holder(t_position **holder, t_token **tokens)
// {
// 	if (*holder == NULL)
// 		return ;
// 	(*holder)->start = 0;
// 	(*holder)->end = 0;
// 	(*holder)->flag = 0;
// 	(*holder)->node_member = affect_index(tokens);
// }

// t_position	*index_getter(t_token **tokens)
// {
// 	t_position	*holder;
// 	t_token		*current;

// 	current = (*tokens);
// 	holder = (t_position *)malloc(sizeof(t_position));
// 	init_holder(&holder, tokens);
// 	while (current && current->next)
// 	{
// 		while (current && current->next && current->index < holder->node_member \
// 			&& true_state(current) && true_state(current->next))
// 		{
// 			if (holder->flag == 0)
// 				holder->start = current->index;
// 			holder->flag = 1;
// 			current = current->next;
// 		}
// 		if (holder->flag)
// 		{
// 			holder->end = current->index;
// 			return (holder);
// 		}
// 		current = current->next;
// 	}
// 	return (holder);
// }

// void	ft_clean(t_token **tokens)
// {
// 	t_token		*cursur;
// 	t_position	*to_extract;
// 	t_token		*node;

// 	cursur = (*tokens);
// 	while (cursur)
// 	{
// 		to_extract = index_getter(tokens);
// 		if (to_extract->start != to_extract->end)
// 		{
// 			node = data_assembler(tokens, to_extract);
// 			ft_free_token(tokens);
// 			add_token(tokens, node);
// 			cursur = (*tokens);
// 		}
// 		cursur = cursur->next;
// 		free(to_extract);
// 	}
// }

// ////////////////////////////////////////////////////////////
// int	ft_segfault(t_token **token)
// {
// 	t_token	*current;

// 	current = *token;
// 	while (current)
// 	{
// 		if (current->type == SYNTAX_ERROR)
// 			return (0);
// 		current = current->next;
// 	}
// 	return (1);
// }

// void	more_analyse(t_token **token)
// {
// 	t_token	*current;

// 	if (!token || !*token)
// 		return ;
// 	current = *token;
// 	while (current)
// 	{
// 		if (search_quote(current->value)
// 			&& (current->state == IN_DQUOT || current->state == IN_SQUOT))
// 		{
// 			current->value = supr_quote(current->value, current->state);
// 			current->state = NORMAL;
// 		}
// 		current = current->next;
// 	}
// 	if (ft_segfault(token) == 1 && (*token)->node_member != 1)
// 		ft_clean(token);
// }

char *remove_quotes(char *value, t_token_state state)
{
    int len = 0, i = 0, j = 0;
    char *result;

    if (!value)
        return NULL;

    // Calculate the length of the string without quotes
    while (value[i]) {
        if ((state == IN_DQUOT && value[i] != '"') || 
            (state == IN_SQUOT && value[i] != '\'')) {
            len++;
        }
        i++;
    }

    result = malloc(len + 1);
    if (!result)
        return NULL;

    i = 0;
    while (value[i]) {
        if ((state == IN_DQUOT && value[i] != '"') || 
            (state == IN_SQUOT && value[i] != '\'')) {
            result[j++] = value[i];
        }
        i++;
    }
    result[j] = '\0';
    free(value);
    return result;
}


void process_quotes(t_token **tokens)
{
    t_token *current = *tokens;

    while (current) {
        if (current->state == IN_DQUOT || current->state == IN_SQUOT) {
            current->value = remove_quotes(current->value, current->state);
            current->state = NORMAL;
        }
        current = current->next;
    }
}


t_token *merge_tokens(t_token *start, t_token *end)
{
    char *merged_value = ft_strdup(start->value);
    t_token *current = start->next;

    while (current && current != end->next) {
        char *temp = ft_strjoin(merged_value, current->value);
        free(merged_value);
        merged_value = temp;
        current = current->next;
    }

    t_token *new_token = create_token(merged_value, CMD, NORMAL);
    new_token->index = start->index;

    free(merged_value);
    return new_token;
}

void replace_tokens(t_token **tokens, t_token *start, t_token *end, t_token *new_token)
{
    t_token *prev = start->prev;
    t_token *next = end->next;

    // Relier le nouveau token à la liste
    if (prev) {
        prev->next = new_token;
        new_token->prev = prev;
    } else {
        // Si le début de la liste est remplacé
        *tokens = new_token;
    }

    if (next) {
        next->prev = new_token;
        new_token->next = next;
    }

    // Libérer les anciens tokens
    t_token *current = start;
    while (current != next) {
        t_token *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
}


void clean_tokens(t_token **tokens)
{
    t_token *current = *tokens;
    t_token *start = NULL, *end = NULL;

    while (current) {
        if (current->state == IN_DQUOT || current->state == IN_SQUOT) {
            if (!start)
                start = current;
            end = current;
        } else if (start && end) {
            t_token *new_token = merge_tokens(start, end);
            replace_tokens(tokens, start, end, new_token);
            current = *tokens; // Restart from the beginning
            start = end = NULL;
        }
        current = current->next;
    }

    if (start && end) {
        t_token *new_token = merge_tokens(start, end);
        replace_tokens(tokens, start, end, new_token);
    }
}


void analyze_tokens(t_token **tokens)
{
    if (!tokens || !*tokens)
        return;

    process_quotes(tokens);
    clean_tokens(tokens);
}
