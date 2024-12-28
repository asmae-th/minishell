/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:27:20 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 13:59:47 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

// void	pipeline(t_final_cmd *cmd, t_envp **envp)
// {
// 	int pipe_fd[2]; // Pipe entre deux commandes
// 	int prev_fd = -1; // Pour stocker pipe_fd[0] de la commande précédente
// 	int pid;
// 	t_final_cmd *cmds = cmd;

// 	while (cmds)
// 	{
// 		char *path = path_trouvé(cmds);
// 		// Créer un pipe si ce n'est pas la dernière commande
// 		if (cmds->next && pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe failed");
// 			if (path != cmds->arr[0]) free(path);
// 			exit(1);
// 		}
// 		// Fork pour la commande actuelle
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork failed in pipe");
// 			if (path != cmds->arr[0]) free(path);
// 			exit(1);
// 		}
// 		if (pid == 0) // Processus enfant
// 		{
// 			if (!path)
// 			{
// 				    char *error_message = cmds->arr[0];
// 					char *suffix = " :hh commande not found\n";
// 					// Afficher l'erreur en utilisant write
// 					write(STDERR_FILENO, error_message, strlen(error_message));
// 					write(STDERR_FILENO, suffix, strlen(suffix));
// 					exit(127); // Code standard pour "commande non trouvée"
// 			}
// 			// Lire depuis le pipe précédent
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			// Écrire dans le prochain pipe (si ce n'est pas la dernière commande)
// 			if (cmds->next)
// 			{
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 				close(pipe_fd[1]);
// 			}
// 			// Fermer les descripteurs inutilisés
// 			close(pipe_fd[0]);
	
// 			// Appliquer les redirections si définies
// 			if (apply_redirections(cmds) == -1)
// 			{
// 				perror("Redirection failed in pipe\n");
// 				if (path != cmds->arr[0]) free(path);
// 				exit(1);
// 			}
// 			printf("check after builtins\n");
// 			if (builtins(cmds, envp) == 0)
// 			{
// 				printf("in builtins\n");
// 				exit(0);
// 			}
// 			close_fds(cmds);
			
//             // Exécuter la commande
// 			char **env = copie_list_in_array(envp);
//             if (execve(path, cmds->arr, env) == -1)
//             {
// 				perror("execve failed");
// 				free_arr(env);
// 				if (path != cmds->arr[0]) free(path);
//                 exit(1);
//             }
//         }
// 		if (path != cmds->arr[0])
// 			free(path);
//         // Fermer les descripteurs inutilisés dans le processus parent
//         if (prev_fd != -1)
//             close(prev_fd);

//         if (cmds->next)
//             close(pipe_fd[1]);

//         prev_fd = pipe_fd[0];
//         cmds = cmds->next;
//     }
//     // Attendre tous les processus enfants
//     while (wait(NULL) > 0)
// 		;
// }

void pipeline(t_final_cmd *cmd, t_envp **envp)
{
    int pipe_fd[2];
    int prev_fd = -1;
    int pid;
    t_final_cmd *cmds = cmd;

    while (cmds)
    {
        if (cmds->next && pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            exit(1);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork failed in pipe");
            exit(1);
        }

        if (pid == 0) // Processus enfant
        {
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

            // Appliquer les redirections
            if (apply_redirections(cmds) == -1)
            {
                perror("Redirection failed in pipeline\n");
                exit(1);
            }
			close_fds(cmds);
            // Vérifier et exécuter les builtins
            if (builtins(cmds, envp) == 0)
            {
                exit(0);
            }

            // Exécution normale
            char *path = path_trouvé(cmds);
            if (!path)
            {
                fprintf(stderr, "%s: command not found\n", cmds->arr[0]);
                exit(127);
            }
            char **env = copie_list_in_array(envp);
            execve(path, cmds->arr, env);
            perror("execve failed");
            free_arr(env);
            exit(1);
        }

        // Gérer les descripteurs dans le parent
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
            close(pipe_fd[1]);
        prev_fd = pipe_fd[0];
        cmds = cmds->next;
    }

    // Attendre tous les enfants
    while (wait(NULL) > 0)
        ;
}
