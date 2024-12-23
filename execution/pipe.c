/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:27:20 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/22 13:45:48 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	pipeline(t_final_cmd *cmd, t_envp *envp)
{
	int pipe_fd[2]; // Pipe entre deux commandes
	int prev_fd = -1; // Pour stocker pipe_fd[0] de la commande précédente
	int pid;
	t_final_cmd *cmds = cmd;

	while (cmds)
	{
		char *path = path_trouvé(cmds);
		// Créer un pipe si ce n'est pas la dernière commande
		if (cmds->next && pipe(pipe_fd) == -1)
		{
			perror("pipe failed");
			if (path != cmds->arr[0]) free(path);
			exit(1);
		}
		// Fork pour la commande actuelle
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed in pipe");
			if (path != cmds->arr[0]) free(path);
			exit(1);
		}
		if (pid == 0) // Processus enfant
		{
			if (!path)
			{
				    char *error_message = cmds->arr[0];
					char *suffix = " : commande not found\n";
					// Afficher l'erreur en utilisant write
					write(STDERR_FILENO, error_message, strlen(error_message));
					write(STDERR_FILENO, suffix, strlen(suffix));
					exit(127); // Code standard pour "commande non trouvée"
			}
			// Lire depuis le pipe précédent
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			// Écrire dans le prochain pipe (si ce n'est pas la dernière commande)
			if (cmds->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			// Fermer les descripteurs inutilisés
			close(pipe_fd[0]);
	
			// Appliquer les redirections si définies
			if (apply_redirections(cmds) == -1)
			{
				perror("Redirection failed in pipe\n");
				if (path != cmds->arr[0]) free(path);
				exit(1);
			}
            // Exécuter la commande
			char **env = copie_list_in_array(envp);
            if (execve(path, cmds->arr, env) == -1)
            {
				perror("execve failed");
				free_arr(env);
				if (path != cmds->arr[0]) free(path);
                exit(1);
            }
        }
		if (path != cmds->arr[0])
			free(path);
        // Fermer les descripteurs inutilisés dans le processus parent
        if (prev_fd != -1)
            close(prev_fd);

        if (cmds->next)
            close(pipe_fd[1]);

        prev_fd = pipe_fd[0];
        cmds = cmds->next;
    }
    // Attendre tous les processus enfants
    while (wait(NULL) > 0)
		;
}

