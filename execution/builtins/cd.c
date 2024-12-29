/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:48 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 00:15:27 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

// #getenv: permet de récupérer la valeur d'une variable d'environnement dans le programme .
// #chdir: change le répértoire courant de processus .
// #perror: afficher un message d'erreur standard basé sur la dernière erreur rencontrée par le système .
// cd met à jour le répertoire courant et les variables PWD et OLDPWD .

void	update_env_pwd(t_envp **envp, char *key, char *value)
{
	char	*update;

	update = ft_strjoin(key, value);
	add_or_apdate_envp(envp, create_noeud(update));
	free(update);
}

void	ft_cd(t_final_cmd *cmd, t_envp **envp)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;

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
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	update_env_pwd(envp, "OLDPWD=", oldpwd);
	pwd = getcwd(NULL, 0);
	update_env_pwd(envp, "PWD=", pwd);
	free_pwd_oldpwd(oldpwd, pwd);
}

void	free_pwd_oldpwd(char *oldpwd, char *pwd)
{
	free(oldpwd);
	free(pwd);
}
