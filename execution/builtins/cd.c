/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:48 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/25 23:34:39 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

// #getenv: permet de récupérer la valeur d'une variable d'environnement dans le programme .
// #chdir: change le répértoire courant de processus .
// #perror: afficher un message d'erreur standard basé sur la dernière erreur rencontrée par le système .
// cd met à jour le répertoire courant et les variables PWD et OLDPWD .

void	ft_cd(t_final_cmd *cmd, t_envp **envp)
{
	char *path;
	char *pwd;
	char *OLDPWD;

	if (cmd->arr[1] == NULL || ft_strcmp(cmd->arr[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: La variable d'environnement HOME n'est pas définie.\n");
			return ;
		}
	}
	else
		path = cmd->arr[1];
	OLDPWD = getcwd(NULL, 0);
	// if (!OLDPWD)
	// {
	// 	perror("getcwd");
	// 	free(OLDPWD);
	// 	return ;
	// }
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	// khasni la mise a jour dyal PWD et OLDPWD
	char *update_oldpwd = ft_strjoin("OLDPWD=", OLDPWD);
	add_or_apdate_envp(envp, create_noeud(update_oldpwd));
	free(update_oldpwd);
	pwd = getcwd(NULL, 0);
	char *update_pwd = ft_strjoin("PWD=", pwd);
	add_or_apdate_envp(envp, create_noeud(update_pwd));
	free(update_pwd);

	free(OLDPWD);
	free(pwd);
}
