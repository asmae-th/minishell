/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:39 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 10:36:18 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	ft_commande(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (!tmp->prev && tmp->v_type == NONE && (!redir_case(tmp->type)))
			tmp->v_type = COMMANDE;
		else if (tmp->type == PIPE && (!redir_case(tmp->next->type))
			&& tmp->next->v_type == NONE)
			tmp->next->v_type = COMMANDE;
		tmp = tmp->next;
	}
}

void	ft_option(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->v_type == NONE && (tmp->type == CMD \
				|| tmp->type == EXIT_STATUS || tmp->type == NEW_TYPE))
			tmp->v_type = ARG;
		tmp = tmp->next;
	}
}

t_final_cmd	*ft_organize_cmd(t_token **token, t_envp **env)
{
	t_tmp_cmd	*tmp;
	t_final_cmd	*final_cmd;

	tmp = NULL;
	final_cmd = NULL;
	new_list(&tmp, token);
	handle_red(&tmp);
	delete_redir(&tmp);
	ft_commande(&tmp);
	ft_option(&tmp);
	if (ft_here_doc(&tmp, env) == 404)
	{
		ft_free_t_tmp_cmd(&tmp);
		return (NULL);
	}
	signal(SIGINT, signal_handler);
	final_commande(&final_cmd, &tmp);
	ft_free_token(token);
	ft_free_t_tmp_cmd(&tmp);
	return (final_cmd);
}

void	ft_free_final_cmd(t_final_cmd **final)
{
	t_final_cmd	*tmp;
	t_final_cmd	*current;
	int			i;

	if (!final || !*final)
		return ;
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

void	ft_free_t_tmp_cmd(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;
	t_tmp_cmd	*current;

	if (!cmd || !*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		tmp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	*cmd = NULL;
}
