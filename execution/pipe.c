/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:27:20 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 13:20:04 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	pipeline(t_final_cmd *cmd, t_envp **envp)
{
	int			pipe_fd[2];
	int			prev_fd;
	int			pid;
	t_final_cmd	*cmds;

	prev_fd = -1;
	cmds = cmd;
	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) == -1)
			handle_error("pipe failed", 1);
		pid = fork();
		if (pid == -1)
			handle_error("fork failed in pipe", 1);
		if (pid == 0)
			execute_child(cmds, envp, prev_fd, pipe_fd);
		close_parent_fds_pipe(prev_fd, pipe_fd, cmds);
		prev_fd = pipe_fd[0];
		cmds = cmds->next;
	}
	wait_all_children(pid);
}

void	preve_fd(int prev_fd)
{
	dup2(prev_fd, STDIN_FILENO);
	close(prev_fd);
}

void	execute_child(t_final_cmd *cmds, t_envp **envp,
			int prev_fd, int pipe_fd[2])
{
	char	*path;
	char	**env;

	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
		preve_fd(prev_fd);
	if (cmds->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	if (apply_redirections(cmds) == -1)
		exit(1);
	close_file_descriptors(3);
	if (builtins(cmds, envp) == 0)
		exit_builtins(envp);
	path = path_trouve(cmds, envp);
	if (!path)
		handle_cmd_not_found(cmds->arr[0], envp);
	env = copie_list_in_array(envp);
	execve(path, cmds->arr, env);
	handle_execve_error(env);
}

void	close_parent_fds_pipe(int prev_fd, int pipe_fd[2], t_final_cmd *cmds)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmds->next)
		close(pipe_fd[1]);
}

void	wait_all_children(int last_pid)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				ft_setter(WEXITSTATUS(status), 1);
			else if (WIFSIGNALED(status))
				ft_setter(128 + WTERMSIG(status), 1);
		}
	}
	if (pid == -1 && errno != ECHILD)
	{
		perror("waitpid failed");
		exit(1);
	}
}
