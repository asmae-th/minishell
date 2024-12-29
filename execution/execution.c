/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:52:17 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 01:07:30 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

void	execute_command_simple(char *path, t_final_cmd *cmd, t_envp **envp)
{
		pid_t	pid = fork();
		if (pid == -1) {
			perror("fork failed");
			exit(1);
		}
		char **env = copie_list_in_array(envp);
		if (pid == 0) // Processus enfant
		{
		// Appliquer les redirections
		if (apply_redirections(cmd) == -1)
		{
			perror("Redirection failed in commande simple\n");
			free_arr(env);
			exit(1);
		}
		close_fds(cmd);
		// Exécuter la commande
		if (execve(path, cmd->arr, env) == -1) {
			perror("execve failed");
			free_arr(env);
			exit(1);
		}
	} else {
		wait(NULL); // Attendre la fin du processus enfant
	}
	free_arr(env);
}

char	*path_trouvé(t_final_cmd *cmd)
{
	char	*path;

	path = NULL;	
	if (cmd->arr[0][0] == '/' || cmd->arr[0][0] == '.')
		path = cmd->arr[0]; //  aucun allocation ici 
	else
		path = find_executable(cmd->arr[0]); // allocation dynamique 
	return (path);
}

int	prepare_and_execute(t_envp **envp, t_final_cmd *cmd)
{
	char	*path;

	path = path_trouvé(cmd);
	if (!path)
	{
		printf("%s : commande not found\n", cmd->arr[0]);
		return(ft_setter(127, 1)); // Code standard pour "commande non trouvée"
	}
	execute_command_simple(path, cmd, envp);
	if (path != cmd->arr[0]) // Vérifier si path est alloué dynamiquement
		free(path);
	return (0);
}

void	execute_command(t_final_cmd *cmd, t_envp **envp)
{
	if (cmd && cmd->next == NULL && builtins(cmd, envp) == 0)
		return ;
	if (cmd->next) // Vérifie si c'est un pipeline
	{
		printf("pipeline exécuté\n");
		pipeline(cmd, envp);
	}
	else // ou si une commande simple
	{
		printf("commande simple exécuté\n");
		prepare_and_execute(envp, cmd);
	}
}

int	execution(t_final_cmd *cmd, t_envp **envp)
{
	if (!cmd)
		return (SYNTAX_ERROR);
	execute_command(cmd, envp);
	// free_list(envp);
	return (0);
}
