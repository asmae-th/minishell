/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_commande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:56:00 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 16:57:22 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	fd_open(t_tmp_cmd *cmd)
{
	int	fd;

	fd = 1;
	if (cmd->f_type == OUT_FILE)
		fd = open(cmd->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (cmd->f_type == APPEND_FILE)
		fd = open(cmd->value, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return (fd);
}

t_in_out	check_fd(t_tmp_cmd **cmd)
{
	t_in_out	fd;
	t_tmp_cmd	*current;

	current = *cmd;
	fd.fd_in = STDIN_FILENO;
	fd.fd_out = STDOUT_FILENO;
	while (current && current->type != PIPE)
	{
		if (current->v_type == TFILE)
		{
			if (current->f_type == OUT_FILE || current->f_type == APPEND_FILE)
			{
				if (fd.fd_out != 1)
					close(fd.fd_out);
				fd.fd_out = fd_open(current);
			}
			else
				fd.fd_in = open(current->value, O_RDONLY, 0666);
			if (fd.fd_in == -1 || fd.fd_out == -1)
			{
				write(STDERR_FILENO, "STDERROR", ft_strlen("STDERROR"));
				return (fd);
			}
		}
		current = current->next;
	}
	return (fd);
}

int	arg_count(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;
	int			nb_arg;

	tmp = *cmd;
	nb_arg = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->v_type == COMMANDE || tmp->v_type == ARG)
			nb_arg++;
		tmp = tmp->next;
	}
	return (nb_arg);
}

char	**cmd_array(t_tmp_cmd **cmd)
{
	char		**arr;
	t_tmp_cmd	*tmp;
	int			i;

	i = 0;
	arr = malloc((arg_count(cmd) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = *cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->v_type == COMMANDE || tmp->v_type == ARG)
		{
			if (tmp->type == EXIT_STATUS)
				arr[i] = ft_itoa(ft_setter(255, 0));
			else
				arr[i] = ft_strndup(tmp->value, ft_strlen(tmp->value));
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

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
