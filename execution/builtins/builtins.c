/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:59 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 13:31:41 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

// int	builtins(char **av, t_envp **envp)
// {
// 	if (apply_redirections(cmd) == -1)
// 		{
// 			perror("Redirection failed in commande simple\n");
// 			free_arr(env);
// 			return (-1);
// 		}
// 	if (!av || !av[0])
// 		return (1);
// 	if (f_strcmp(av[0], "echo") == 0)
// 		ft_echo(av);
// 	else if (f_strcmp(av[0], "cd") == 0)
// 		ft_cd(av);
// 	else if (f_strcmp(av[0], "pwd") == 0)
// 		ft_pwd();
// 	else if (f_strcmp(av[0], "exit") == 0)
// 		ft_exit(av);
// 	else if (f_strcmp(av[0], "env") == 0)
// 		ft_envp(*envp);
// 	else if (f_strcmp(av[0], "unset") == 0)
// 		ft_unset(envp, av);
// 	else if (f_strcmp(av[0], "export") == 0)
// 		ft_export(envp, av);
// 	else
// 		return (1);
// 	return (0);
// }

// int	builtins(t_final_cmd *cmd, t_envp **envp)
// {
// 	if (apply_redirections(cmd) == -1)
// 	{
// 		perror("Redirection failed in builtins\n");
// 		return (-1);
// 	}
// 	if (!cmd->arr || !cmd->arr[0])
// 		return (1);
// 	if (f_strcmp(cmd->arr[0], "echo") == 0)
// 		ft_echo(cmd);
// 	else if (f_strcmp(cmd->arr[0], "cd") == 0)
// 		ft_cd(cmd, envp);
// 	else if (f_strcmp(cmd->arr[0], "pwd") == 0)
// 		ft_pwd();
// 	else if (f_strcmp(cmd->arr[0], "exit") == 0)
// 		ft_exit(cmd);
// 	else if (f_strcmp(cmd->arr[0], "env") == 0)
// 		ft_envp(envp);
// 	else if (f_strcmp(cmd->arr[0], "unset") == 0)
// 		ft_unset(envp, cmd);
// 	else if (f_strcmp(cmd->arr[0], "export") == 0)
// 		ft_export(envp, cmd);
// 	else
// 		return (1);
// 	return (0);
// }

void restaure_redirection(int saved_stdout, int saved_stdin)
{
		dup2(saved_stdout, STDOUT_FILENO); // Restaurer STDOUT
		close(saved_stdout);
		dup2(saved_stdin, STDIN_FILENO);  // Restaurer STDIN
		close(saved_stdin);
}

int	builtins(t_final_cmd *cmd, t_envp **envp)
{
	int saved_stdout = dup(STDOUT_FILENO); // Sauvegarder STDOUT
	int saved_stdin = dup(STDIN_FILENO);  // Sauvegarder STDIN

	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("dup failed");
		return (-1);
	}
	if (apply_redirections(cmd) == -1)
	{
		perror("Redirection failed in builtins");
		restaure_redirection(saved_stdout, saved_stdin);
		return (-1);
	}
	if (!cmd->arr || !cmd->arr[0])
		return (1);
	if (f_strcmp(cmd->arr[0], "echo") == 0)
		ft_echo(cmd);
	else if (f_strcmp(cmd->arr[0], "cd") == 0)
		ft_cd(cmd, envp);
	else if (f_strcmp(cmd->arr[0], "pwd") == 0)
		ft_pwd();
	else if (f_strcmp(cmd->arr[0], "exit") == 0)
		ft_exit(cmd);
	else if (f_strcmp(cmd->arr[0], "env") == 0)
		ft_envp(envp);
	else if (f_strcmp(cmd->arr[0], "unset") == 0)
		ft_unset(envp, cmd);
	else if (f_strcmp(cmd->arr[0], "export") == 0)
		ft_export(envp, cmd);
	else
	{
		restaure_redirection(saved_stdout, saved_stdin);
		return (1);
	}
	restaure_redirection(saved_stdout, saved_stdin);
	return (0);
}
