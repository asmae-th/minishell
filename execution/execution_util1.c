/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:50:41 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/01 21:40:30 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	execute_child_process(char *path, t_final_cmd *cmd,
			char **env, t_envp **envp)
{
	if (apply_redirections(cmd) == -1)
	{
		perror("Redirection failed in simple command");
		free_arr(env);
		free_list(*envp);
		exit(1);
	}
	close_fds(cmd);
	if (execve(path, cmd->arr, env) == -1)
	{
		perror("execve failed");
		ft_free_final_cmd(&cmd);
		free_list(*envp);
		free_arr(env);
		exit(127);
	}
}

void	execute_command_simple(char *path, t_final_cmd *cmd, t_envp **envp)
{
	pid_t	pid;
	int		status;
	char	**env;

	status = 0;
	pid = fork();
	env = copie_list_in_array(envp);
	if (pid == -1)
		handle_error("fork failed", 1);
	if (pid == 0)
		execute_child_process(path, cmd, env, envp);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			handle_error("waitpid faild", 1);
		if (WIFEXITED(status))
			ft_setter(WEXITSTATUS(status), 1);
		if (WIFSIGNALED(status))
			ft_setter(130, 1);
	}
	free_arr(env);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}
