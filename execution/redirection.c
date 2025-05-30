/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:29:37 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 00:58:45 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	apply_redirections(t_final_cmd *redir)
{
	if (redir->fd_out != STDOUT_FILENO)
	{
		if (redir->fd_out == -1)
			return (-1);
		if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for fd_out");
			close(redir->fd_out);
			return (-1);
		}
	}
	if (redir->fd_in != STDIN_FILENO)
	{
		if (redir->fd_in == -1)
			return (-1);
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for fd_in");
			close(redir->fd_in);
			return (-1);
		}
	}
	return (0);
}

void	close_fds(t_final_cmd *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
		close(cmd->fd_out);
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
		close(cmd->fd_in);
}
