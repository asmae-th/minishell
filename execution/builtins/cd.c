/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:48 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 15:12:36 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	update_env_pwd(t_envp **envp, char *key, char *value)
{
	char	*update;

	if (!key || ! value)
		return ;
	update = ft_strjoin(key, value);
	add_or_apdate_envp(envp, create_noeud(update));
	free(update);
}

int	ft_cd(t_final_cmd *cmd, t_envp **envp)
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
			return (EXIT_FAILURE);
		}
	}
	else
		path = cmd->arr[1];
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		return (perror("cd"), EXIT_FAILURE);
	update_env_pwd(envp, "OLDPWD=", oldpwd);
	pwd = getcwd(NULL, 0);
	update_env_pwd(envp, "PWD=", pwd);
	free_pwd_oldpwd(oldpwd, pwd);
	return (OK);
}

void	free_pwd_oldpwd(char *oldpwd, char *pwd)
{
	free(oldpwd);
	free(pwd);
}
