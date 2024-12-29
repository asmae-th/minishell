/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:52:17 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 18:18:51 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

// void	execute_command_simple(char *path, t_final_cmd *cmd, t_envp **envp)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	**env;

// 	pid = fork();
// 	env = copie_list_in_array(envp);
// 	if (pid == -1)
// 	{
// 		perror("fork failed");
// 		free_arr(env);
// 		exit(1);
// 	}
// 	if (pid == 0) // Processus enfant
// 	{
// 		if (apply_redirections(cmd) == -1)// Appliquer les redirections
// 		{
// 			perror("Redirection failed in commande simple");
// 			free_arr(env);
// 			exit(1);
// 		}
// 		close_fds(cmd);
// 		if (execve(path, cmd->arr, env) == -1)// Exécuter la commande
// 		{
// 			perror("execve failed");
// 			free_arr(env);
// 			exit(1); // On sort avec un statut d'erreur
// 		}
// 	}
// 	else // Processus parent
// 	{
// 		if (waitpid(pid, &status, 0) == -1)// Attendre la fin du processus enfant
// 		{
// 			perror("waitpid failed");
// 			free_arr(env);
// 			exit(1);
// 		}
// 		if (WIFEXITED(status))// Vérifier si le processus s'est terminé normalement
// 		{
// 			int exit_status = WEXITSTATUS(status);
// 			ft_setter(exit_status, 1); // Met à jour $? avec le statut de sortie de l'enfant
// 		}
// 		else if (WIFSIGNALED(status))
// 		{
// 			int signal_status = 128 + WTERMSIG(status);
// 			ft_setter(signal_status, 1); // Met à jour $? avec le signal
// 		}
// 	}
// 	free_arr(env);
// }

void execute_child_process(char *path, t_final_cmd *cmd, char **env)
{
    if (apply_redirections(cmd) == -1) // Appliquer les redirections
    {
        perror("Redirection failed in simple command");
        free_arr(env);
        exit(1);
    }
    close_fds(cmd);
    if (execve(path, cmd->arr, env) == -1) // Exécuter la commande
    {
        perror("execve failed");
        free_arr(env);
        exit(1); // On sort avec un statut d'erreur
    }
}

void execute_command_simple(char *path, t_final_cmd *cmd, t_envp **envp)
{
    pid_t pid;
    int status;
    char **env;

    pid = fork();
    env = copie_list_in_array(envp);
    if (pid == -1)
		handle_error("fork failed", 1);
    if (pid == 0) // Processus enfant
        execute_child_process(path, cmd, env); // Appel à la fonction qui gère l'exécution de l'enfant
    else // Processus parent
    {
        if (waitpid(pid, &status, 0) == -1) // Attendre la fin du processus enfant
        {
            perror("waitpid failed");
            free_arr(env);
            exit(1);
        }
        if (WIFEXITED(status)) // Vérifier si le processus s'est terminé normalement
            ft_setter(WEXITSTATUS(status), 1); // Met à jour $? avec le statut de sortie de l'enfant
        else if (WIFSIGNALED(status))
            ft_setter(128 + WTERMSIG(status), 1); // Met à jour $? avec le signal
    }
    free_arr(env);
}


int	is_directory(const char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return 1;
	return 0;
}

char	*path_trouve(t_final_cmd *cmd, t_envp **env)
{
	char	*path;

	if (!cmd || !cmd->arr || !cmd->arr[0])
		return (NULL);
	path = NULL;
	if (cmd->arr[0][0] == '/' || cmd->arr[0][0] == '.')
		path = cmd->arr[0]; //  aucun allocation ici 
	else
		path = find_executable(cmd->arr[0], env); // allocation dynamique 
	return (path);
}

int	prepare_and_execute(t_envp **envp, t_final_cmd *cmd)
{
	char	*path;

	path = path_trouve(cmd, envp);
	if (!path)
	{
		printf("%s : commande not found\n", cmd->arr[0]);
		return(ft_setter(127, 1)); // Code standard pour "commande non trouvée"
	}
	// Vérifier si c'est un répertoire
	if (is_directory(path))
	{
		printf("%s: is a directory\n", path);
		if (path != cmd->arr[0]) // Si alloué dynamiquement
			free(path);
		return ft_setter(126, 1); // Code standard pour "Permission denied ou is a directory"
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
	// close_file_descriptors(3);
	return (0);
}
