/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_commande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:56:00 by asmae             #+#    #+#             */
/*   Updated: 2024/12/31 13:51:24 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_final_cmd	*creat_final_cmd(t_tmp_cmd **cmd)
{
	t_final_cmd	*node;
	t_in_out	fd;

	fd = check_fd(cmd);
	node = (t_final_cmd *)malloc(sizeof(t_final_cmd));
	if (!node)
		return (NULL);
	node->arr = cmd_array(cmd);
	node->fd_in = fd.fd_in;
	node->fd_out = fd.fd_out;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_final_list(t_final_cmd **f_cmd, t_final_cmd *node)
{
	t_final_cmd	*tmp;

	if (!(*f_cmd))
	{
		(*f_cmd) = node;
	}
	else
	{
		tmp = *f_cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

t_tmp_cmd	*ft_next(t_tmp_cmd *cmd)
{
	while (cmd && cmd->type != PIPE)
		cmd = cmd->next;
	if (cmd && cmd->type == PIPE)
		cmd = cmd->next;
	return (cmd);
}

void	final_commande(t_final_cmd **f_cmd, t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		add_final_list(f_cmd, creat_final_cmd(&tmp));
		tmp = ft_next(tmp);
	}
}
