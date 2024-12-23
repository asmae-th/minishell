/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:39 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 11:11:47 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

tmp_cmd	*creat_new_cmd(char *value, t_token_type type, t_token_state state, t_herdoc valid)
{
	tmp_cmd *new_cmd;
	
	new_cmd = malloc(sizeof(tmp_cmd));
	if(!new_cmd)
		return(NULL);
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
void	add_new_cmd(tmp_cmd **cmd, tmp_cmd *new_cmd)
{
	tmp_cmd *tmp;
	
	if(!(*cmd))
		(*cmd) = new_cmd;
	else
	{
		tmp = *cmd;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

void    new_list(tmp_cmd **tmp, t_token **token)
{
	t_token	*tmp_token;

	tmp_token = *token;
	while (tmp_token)
	{
		if(tmp_token->type != A_SPACE)
			add_new_cmd(tmp,creat_new_cmd(tmp_token->value, tmp_token->type, tmp_token->state, tmp_token->valid));
		tmp_token = tmp_token->next;
	}
	
}
void	red_file(tmp_cmd **cmd)
{
	tmp_cmd *current;

	current = *cmd;

	while (current)
	{
		if(redir_case(current->type))
			current->next->v_type = TFILE;
		if(current->type == OUT_REDIR)
			current->next->f_type = OUT_FILE;
		if(current->type == IN_REDIR)
			current->next->f_type = IN_FILE;
		if(current->type == APPEND)
			current->next->f_type = APPEND_FILE;
		if(current->type == HERE_DOC)
			current->next->f_type = HEREDOC_FILE;
		current = current->next;
	}
	
}

void	handle_red(tmp_cmd **cmd)
{
	tmp_cmd	*current;
	tmp_cmd	*tmp;

	current = *cmd;
	while (current)
	{
		if(current->type == OUT_REDIR && current->next->type == PIPE)
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

void	delete_redir(tmp_cmd **cmd)
{
	tmp_cmd	*current;
	tmp_cmd	*temp;

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

void	ft_commande(tmp_cmd **cmd)
{
	tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (!tmp->prev && tmp->v_type == NONE && (!redir_case(tmp->type)))
			tmp->v_type = COMMANDE;
		else if (tmp->type == PIPE && (!redir_case(tmp->next->type)) && tmp->next->v_type == NONE)
			tmp->next->v_type = COMMANDE;
		tmp = tmp->next;
	}
}

void	ft_option(tmp_cmd **cmd)
{
	tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->v_type == NONE && (tmp->type == CMD \
				|| tmp->type == EXIT_STATUS))
			tmp->v_type = ARG;
		tmp = tmp->next;
	}
}

t_final_cmd *ft_organize_cmd(t_token **token, t_env **env)
{
	tmp_cmd *tmp;
	t_final_cmd *final_cmd;
	
	tmp = NULL;
	final_cmd = NULL;
	new_list(&tmp, token);
	handle_red(&tmp);
	delete_redir(&tmp);
	ft_commande(&tmp);
	ft_option(&tmp);
	//herdoc
	ft_here_doc(&tmp, env);
	// tmp_cmd	*tmp1 = tmp;
	// 	while (tmp1)
	// 	{
	// 			printf("token : %s and type %d\n",tmp1->value, tmp1->f_type);
	// 			tmp1 = tmp1->next;
	// 	}
	final_commande(&final_cmd, &tmp);
	ft_free_token(token);
	ft_free_tmp_cmd(&tmp);
	// ft_free_env(env);
	return(final_cmd);
}
void	ft_free_final_cmd(t_final_cmd **final)
{
	t_final_cmd	*tmp;
	t_final_cmd	*current;
	int			i;

	if (!final || !*final)
		return;
	current = *final;
	while (current)
	{
		tmp = current->next;
		i = 0;
		if (current->arr)
		{
			while (current->arr[i])
			{
				free(current->arr[i]);
				i++;
			}
			free(current->arr);
		}
		free(current);
		current = tmp;
	}
	*final = NULL;
}


void ft_free_tmp_cmd(tmp_cmd **cmd)
{
	tmp_cmd *tmp;
	tmp_cmd *current;

	if(!cmd || !*cmd)
		return;
	current = *cmd;
	while (current)
	{
		tmp = current->next;
		if(current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	*cmd = NULL;
}