/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_analyse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:00:09 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 14:53:46 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int search_quote(char *value)
{
	int i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if(value[i] == '\"' || value[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int len_value(char *value, t_token_state state)
{
	int i;
	int len;
	
	i = 0;
	len = 0;
	if(state == IN_DQUOT)
	{	
		while (value[i])
		{
		if(value[i] != '\"')
				len++;
			i++;
		}
	}
	else if(state == IN_SQUOT)
	{	
		while (value[i])
		{
		if(value[i] != '\'')
				len++;
			i++;
		}
	}
	return (len);
}
char    *supr_quote(char *value, t_token_state state)
{
	int i;
	int	j;
	char *ptr;

	ptr = (char *)malloc((len_value(value, state) + 1) * sizeof(char));
	if(!ptr)
		return (NULL);
	i = 0;
	j = 0;
	if(state == IN_DQUOT)
	{
		while (value[i])
		{
			if(value[i] != '\"')
			{
				ptr[j] = value[i];
				j++;
			}
			i++;
		}
	}
	else if(state == IN_SQUOT)
	{
		while (value[i])
		{
			if(value[i] != '\'')
			{
				ptr[j] = value[i];
				j++;
			}
			i++;
		}
	}
	ptr[j] = '\0';
	free(value);
	return (ptr);
}

// void	ft_pos_init(t_position **pos, t_token **token)
// {
// 	t_token *current;
// 	int	nb_node;

// 	nb_node = 0;
// 	if(!pos)
// 		return;
// 	(*pos)->start = 0;
// 	(*pos)->end = 0;
// 	(*pos)->flag = 0;
// 	current = (*token);
// 	while (current)
// 	{
// 		current->index = nb_node;
// 		nb_node++;
// 		current = current->next;
// 	}	
// 	(*pos)->node_member = nb_node;
// }

// int	ft_state_check(t_token *token)
// {
// 	if(token->type != EXIT_STATUS &&
// 	(token->state == IN_DQUOT || token->state == IN_SQUOT || token->type == CMD))
// 		return (1);
// 	else
// 		return (0);
// }

// t_position	*ft_get_pos(t_token **token)
// {
// 	t_token	*current;
// 	t_position *pos;
	
// 	pos = (t_position *)malloc(sizeof(t_position));
// 	ft_pos_init(&pos, token);
// 	current = *token;
// 	while (current && current->next)
// 	{
// 		while (current && current->next && current->index < pos->node_member
// 				&& ft_state_check(current) && ft_state_check(current->next))
// 		{
// 			if(pos->flag == 0)
// 				pos->start = current->index;
// 			pos->flag = 1;
// 			current = current->next;
// 			if(pos->flag)
// 			{
// 				pos->end = current->index;
// 				return (pos);
// 			}
// 		}	
// 		current = current->next;
// 	}
// 	return (pos);
// }

// char	*ft_value(t_token *token, int end)
// {
// 	char *ptr;
	
// 	ptr = ft_strndup(token->value, (int)ft_strlen(token->value));
// 	while (token->index < end)
// 	{
// 		ptr = ft_strjoin(ptr, token->next->value);
// 		token = token->next;
// 	}
// 	return (ptr);
// }

// t_token *new_clean_node(t_token **token, t_position *pos)
// {
// 	t_token	*current;
// 	t_token *node;

// 	current = *token;
// 	while (current)
// 	{
// 		if(current->index == pos->start)
// 		{
// 			node = create_token(ft_value(current, pos->end), CMD, NORMAL);
// 			node->index = pos->start;
// 			node->prev = current->prev;
// 		}
// 		if(current->index == pos->end)
// 			node->next = current->next;
// 		current = current->next;
// 	}
// 	return (node);
// }

// void ft_free_start_end(t_token **start, t_token **end)
// {
// 	t_token *current;
// 	t_token *tmp;

// 	current = *start;
// 	while (current)
// 	{
// 		tmp = current->next;
// 		free(current->value);
// 		free(current);
// 		current = tmp;
// 		if(current == *end)
// 		{
// 			free(current->value);
// 			free(current);
// 			break;
// 		}
// 	}
	
// }
// void	add_clean_node(t_token **token , int i_start, int i_end, t_token *clean_node)
// {
// 	t_token *start;
// 	t_token *end;
// 	int i;
	
// 	start = *token;
// 	end = *token;
// 	i = -1;
// 	while (++i < i_start && start != NULL)
// 		start = start->next;
// 	i = -1;
// 	while (++i < i_end && end != NULL)
// 		end = end->next;
// 	if(end->prev == NULL)
// 		*token = clean_node;
// 	else
// 		start->prev->next = clean_node;
// 	if(end->next != NULL)
// 		end->next->prev = clean_node;
// 	clean_node->prev = start->prev;
// 	clean_node->next = end->next;
// 	ft_free_start_end(&start, &end);
// 		// printf("freeeee");
// }

// void	ft_clean(t_token **token)
// {
// 	t_token *current;
// 	t_position *pos;
	
// 	current = *token;
// 	while (current)
// 	{
// 		pos = ft_get_pos(token);
// 		if(pos->start != pos->end)
// 		{
// 			add_clean_node(token, pos->start, pos->end, new_clean_node(token, pos));
// 			current = *token;
// 		}
// 		current = current->next;
// 		free(pos);
// 	}
// }










char	*assemble_data(t_token *begin, int end)
{
	char	*join;

	join = ft_strndup(begin->value, (int)ft_strlen(begin->value));
	while (begin->index < end)
	{
		join = ft_strjoin(join, begin->next->value);
		begin = begin->next;
	}
	return (join);
}

// t_token	*build_new_token_node(char *token_data, enum e_token_type type,
// 		enum e_token_state state)
// {
// 	t_token	*token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->value = token_data;
// 	token->type = type;
// 	token->state = state;
// 	token->index = 0;
// 	token->node_member = 0;
// 	token->next = NULL;
// 	token->prev = NULL;
// 	return (token);
// }

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

void	addclean_token(t_token **head, int start_index, int end_index, t_token *clean_node)
{
	t_token	*start;
	t_token	*end;
	int				i;

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
		t_token	*tmp = *head;
			while (tmp)
			{
					printf("%s\n",tmp->value);
					tmp = tmp->next;
			}
	// free_region(&start, &end);
}

int	true_state(t_token *current)
{
	return (current->type != EXIT_STATUS && \
		(current->state == IN_SQUOT || \
		current->state == IN_DQUOT || current->type == CMD));
}

int	affect_index(t_token **token)
{
	t_token	*cursur;
	int				node_member;

	node_member = 0;
	cursur = (*token);
	while (cursur)
	{
		cursur->index = node_member;
		node_member++;
		cursur = cursur->next;
	}
	// printf("%d\n",node_member);<
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
	t_position		*holder;
	t_token	*current;

	current = (*tokens);
	holder = (t_position *)malloc(sizeof(t_position));
	init_holder(&holder, tokens);
	while (current && current->next)
	{
		while (current && current->next && current->index < holder->node_member \
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

void	ft_clean(t_token **tokens)
{
	t_token	*cursur;
	t_position		*to_extract;
	

	cursur = (*tokens);
	while (cursur)
	{
		to_extract = index_getter(tokens);
		if (to_extract->start != to_extract->end)
		{
			t_token *node;
			node = data_assembler(tokens, to_extract);
			ft_free_token(tokens);
			add_token(tokens, node);
			// addclean_token(tokens, to_extract->start, to_extract->end, node);
			cursur = (*tokens);
		}
		cursur = cursur->next;
		free(to_extract);
	}
	
}

////////////////////////////////////////////////////////////
int	ft_segfault(t_token **token)
{
	t_token *current;

	current = *token;
	while (current)
	{
		if(current->type == SYNTAX_ERROR)
			return (0);
		current = current->next;
	}
	return (1);
}

void    more_analyse(t_token **token)
{
	t_token *current;

	if (!token || !*token)
    return;
	current = *token;
	while (current)
	{
		if (search_quote(current->value) && (current->state == IN_DQUOT || current->state == IN_SQUOT))
		{
			current->value = supr_quote(current->value, current->state);
			current->state = NORMAL;
		}
		current = current->next;
	}
	if(ft_segfault(token) == 1)
		ft_clean(token);
	
}


