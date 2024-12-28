/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:52:17 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 13:28:35 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

char	**copie_list_in_array(t_envp **envp)
{
	char	**array;
	t_envp	*tmp;
	int		i;
	int len;

	if (!envp)
		return NULL;
	i = 0;
	tmp = *envp;
	len = size_list(envp);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	while (tmp)
	{
		array[i] = ft_strdup(tmp->env);
		if (!array[i])
		{
			free_arr(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

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

void	free_arr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*find_executable(char *cmd)
{
	char *path = getenv("PATH");
	if (!path)
		return (NULL);
	char **directories = ft_split(path, ':');
	char *full_path = NULL;
	int 	i = 0;
	while (directories[i])
	{
		full_path = ft_strjoin(directories[i], "/");
		char *temp_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(temp_path, X_OK) == 0)
		{
			free_arr(directories);
			return (temp_path);
		}
		free(temp_path);
		i++;
	}
	free_arr(directories);
	return (NULL);
}

char *path_trouvé(t_final_cmd *cmd)
{
	char *path;

	path = NULL;	
	if (cmd->arr[0][0] == '/' || cmd->arr[0][0] == '.')
		path = cmd->arr[0]; //  aucun allocation ici 
	else
		path = find_executable(cmd->arr[0]); // allocation dynamique 
	return (path);
}

int	prepare_and_execute(t_envp **envp, t_final_cmd *cmd)
{
	char *path;

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
	if ( cmd && cmd->next == NULL && builtins(cmd, envp) == 0)
	{
		printf(" check builtins in execution\n");
		return ;
	}
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
	// close_fds(cmd);
	// free_list(new_env);
	return (0);
}
