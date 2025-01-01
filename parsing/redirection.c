/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:07:03 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 10:26:05 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*ft_red_in(char *input, t_token **token,
	t_token_type type, t_token_state state)
{
	int	i;

	i = 1;
	while (input[i] && input[i] == '<')
		i++;
	if (i == 2)
		add_token(token, create_token(ft_strndup(input, i), HERE_DOC, state));
	else if (i == 1)
		add_token(token, create_token(ft_strndup(input, i), type, state));
	else
	{
		type = SYNTAX_ERROR;
		state = RED_ERR;
		add_token(token, create_token(ft_strdup("RED ERROR"), type, state));
	}
	return (input + i);
}

char	*ft_red_out(char *input, t_token **token,
	t_token_type type, t_token_state state)
{
	int	i;

	i = 1;
	while (input[i] && input[i] == '>')
		i++;
	if (i == 2)
		add_token(token, create_token(ft_strndup(input, 2), APPEND, state));
	else if (i == 1)
	{
		add_token(token, create_token(ft_strndup(input, 2), type, state));
	}
	else
	{
		type = SYNTAX_ERROR;
		state = RED_ERR;
		add_token(token, create_token(ft_strdup("RED ERROR"), type, state));
	}
	return (input + i);
}

char	*ft_home(char *input, t_token **token)
{
	add_token(token, create_token(ft_strndup("$HOME",
				ft_strlen("$HOME")), ENV_VAR, NORMAL));
	return (input + 1);
}

void	delete_redir(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*current;
	t_tmp_cmd	*temp;

	current = *cmd;
	while (current != NULL)
	{
		if (current->type == IN_REDIR || current->type == OUT_REDIR \
			|| current->type == HERE_DOC || current->type == APPEND)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*cmd = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			temp = current;
			current = current->next;
			free(temp->value);
			free(temp);
		}
		else
			current = current->next;
	}
}
