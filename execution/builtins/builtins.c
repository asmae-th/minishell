/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:59 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 19:49:08 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	restaure_redirection(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	execute_builtin(t_final_cmd *cmd, t_envp **envp)
{
	if (f_strcmp(cmd->arr[0], "echo") == 0)
		ft_setter(ft_echo(cmd), 1);
	else if (f_strcmp(cmd->arr[0], "cd") == 0)
		ft_setter(ft_cd(cmd, envp), 1);
	else if (f_strcmp(cmd->arr[0], "pwd") == 0)
		ft_setter(ft_pwd(envp), 1);
	else if (f_strcmp(cmd->arr[0], "exit") == 0)
		ft_setter(ft_exit(cmd, envp), 1);
	else if (f_strcmp(cmd->arr[0], "env") == 0)
		ft_setter(ft_envp(envp, cmd), 1);
	else if (f_strcmp(cmd->arr[0], "unset") == 0)
		ft_setter(ft_unset(envp, cmd), 1);
	else if (f_strcmp(cmd->arr[0], "export") == 0)
		ft_setter(ft_export(envp, cmd), 1);
	else
		return (2);
	return (0);
}

int	builtins(t_final_cmd *cmd, t_envp **envp)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("dup failed");
		return (-1);
	}
	if (apply_redirections(cmd) == -1)
	{
		restaure_redirection(saved_stdout, saved_stdin);
		return (-1);
	}
	if (!cmd->arr || !cmd->arr[0])
		return (1);
	if (execute_builtin(cmd, envp) == 2)
	{
		restaure_redirection(saved_stdout, saved_stdin);
		return (1);
	}
	restaure_redirection(saved_stdout, saved_stdin);
	return (0);
}
