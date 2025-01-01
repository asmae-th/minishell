/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:06:32 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/01 10:37:17 by asmae            ###   ########.fr       */
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
				return (perror(current->value), fd);
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
