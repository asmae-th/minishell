/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:27:20 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 20:20:52 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

// void pipeline(t_final_cmd *cmd, t_envp **envp)
// {
// 	int pipe_fd[2];
// 	int prev_fd = -1;
// 	int pid;
// 	t_final_cmd *cmds = cmd;

// 	while (cmds)
// 	{
// 		if (cmds->next && pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe failed");
// 			exit(1);
// 		}

// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}

// 		if (pid == 0) // Processus enfant
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if (cmds->next)
// 			{
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 				close(pipe_fd[1]);
// 			}
// 			close(pipe_fd[0]);

// 			// Appliquer les redirections
// 			if (apply_redirections(cmds) == -1)
// 			{
// 				perror("Redirection failed in pipeline\n");
// 				exit(1);
// 			}
// 			close_fds(cmds);
// 			// Vérifier et exécuter les builtins
// 			if (builtins(cmds, envp) == 0)
// 			{
// 				exit(0);
// 			}

// 			// Exécution normale
// 			char *path = path_trouve(cmds, envp);
// 			if (!path)
// 			{
// 				fprintf(stderr, "%s: command not found\n", cmds->arr[0]);
// 				exit(127);
// 			}
// 			char **env = copie_list_in_array(envp);
// 			execve(path, cmds->arr, env);
// 			perror("execve failed");
// 			free_arr(env);
// 			exit(1);
// 		}
// 		// Gérer les descripteurs dans le parent
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (cmds->next)
// 			close(pipe_fd[1]);
// 		prev_fd = pipe_fd[0];
// 		cmds = cmds->next;
// 	}

// 	// Attendre tous les enfants
// 	while (wait(NULL) > 0)
// 		;
// }

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

void	execute_child(t_final_cmd *cmds, t_envp **envp, int prev_fd, int pipe_fd[2])
{
	char	*path;
	char	**env;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmds->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	if (apply_redirections(cmds) == -1)
		handle_error("Redirection failed in pipeline", 1);
	close_fds(cmds);
	if (builtins(cmds, envp) == 0)
		exit(0);
	path = path_trouve(cmds, envp);
	if (!path)
		handle_cmd_not_found(cmds->arr[0]);
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

// void	wait_all_children(int pid)
// {
// 	int status;
// 	 if (waitpid(pid, &status, 0) == -1) // Attendre la fin du processus enfant
//         {
//             perror("waitpid failed");
//             exit(1);
//         }
//         if (WIFEXITED(status)) // Vérifier si le processus s'est terminé normalement
//             ft_setter(WEXITSTATUS(status), 1); // Met à jour $? avec le statut de sortie de l'enfant
//         else if (WIFSIGNALED(status))
//             ft_setter(128 + WTERMSIG(status), 1); // Met à jour $? avec le signal
// }

void	wait_all_children(int last_pid)
{
	int status;
	pid_t pid;

	while ((pid = waitpid(-1, &status, 0)) > 0) // Attend tous les processus enfants
	{
		if (pid == last_pid) // Vérifie si c'est le dernier processus attendu
		{
			if (WIFEXITED(status)) // Si le processus s'est terminé normalement
				ft_setter(WEXITSTATUS(status), 1); // Met à jour $? avec le statut de sortie
			else if (WIFSIGNALED(status)) // Si le processus a été terminé par un signal
				ft_setter(128 + WTERMSIG(status), 1); // Met à jour $? avec le signal
		}
	}
	if (pid == -1 && errno != ECHILD) // Si `waitpid` échoue pour une raison autre que l'absence d'enfants
	{
		perror("waitpid failed");
		exit(1);
	}
}
