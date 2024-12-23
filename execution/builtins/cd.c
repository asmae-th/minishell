/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:48 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/15 18:27:29 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
// #getenv: permet de récupérer la valeur d'une variable d'environnement dans le programme .
// #chdir: change le répértoire courant de processus.
// #perror: afficher un message d'erreur standard basé sur la dernière erreur rencontrée par le système .

void	ft_cd(char **av)
{
	char *path;
	if (av[1] == NULL || ft_strcmp(av[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: La variable d'environnement HOME n'est pas définie.\n");
			return ;
		}
	}
	else
		path = av[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	// Afficher le répertoire courant après chaque changement
	// char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL)
    //     printf("Répertoire actuel: %s\n", cwd);
    // else
    //     perror("getcwd");
}
