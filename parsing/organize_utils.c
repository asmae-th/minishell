/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:17:31 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/01 15:24:52 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_tmp_cmd	*creat_new_cmd(char *value, t_token_type type,
	t_token_state state, t_herdoc valid)
{
	t_tmp_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_tmp_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->value = ft_strdup(value);
	new_cmd->type = type;
	new_cmd->state = state;
	new_cmd->valid = valid;
	new_cmd->f_type = NONEF;
	new_cmd->v_type = NONE;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	add_new_cmd(t_tmp_cmd **cmd, t_tmp_cmd *new_cmd)
{
	t_tmp_cmd	*tmp;

	if (!(*cmd))
		(*cmd) = new_cmd;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

void	new_list(t_tmp_cmd **tmp, t_token **token)
{
	t_token	*tmp_token;

	tmp_token = *token;
	while (tmp_token)
	{
		if (tmp_token->type != A_SPACE && tmp_token->type != SLASH)
			add_new_cmd(tmp, creat_new_cmd(tmp_token->value,
					tmp_token->type, tmp_token->state, tmp_token->valid));
		tmp_token = tmp_token->next;
	}
}

void	red_file(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*current;

	current = *cmd;
	while (current)
	{
		if (redir_case(current->type))
			current->next->v_type = TFILE;
		if (current->type == OUT_REDIR)
			current->next->f_type = OUT_FILE;
		if (current->type == IN_REDIR)
			current->next->f_type = IN_FILE;
		if (current->type == APPEND)
			current->next->f_type = APPEND_FILE;
		if (current->type == HERE_DOC)
			current->next->f_type = HEREDOC_FILE;
		current = current->next;
	}
}

void	handle_red(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*current;
	t_tmp_cmd	*tmp;

	current = *cmd;
	while (current)
	{
		if (current->type == OUT_REDIR && current->next->type == PIPE)
		{
			tmp = current->next;
			current->next->next->prev = current;
			current->next = current->next->next;
			free(tmp->value);
			free(tmp);
			current = (*cmd);
		}
		current = current->next;
	}
	red_file(cmd);
}
