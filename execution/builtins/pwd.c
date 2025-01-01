/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:58 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 21:25:39 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #getcwd: récupère le chemin absolu du répertoire de travail actuel .

#include "../../include/execution.h"

char	*get_pwd(t_envp **envp)
{
	t_envp	*tmp;
	char	*pwd;

	tmp = *envp;
	while (tmp)
	{
		if (f_strcmp(tmp->var, "PWD") == 0)
		{
			pwd = tmp->val;
			return (pwd);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_pwd(t_envp **envp)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
		return (OK);
	}
	else
	{
		pwd = get_pwd(envp);
		if (pwd != NULL)
		{
			write(1, pwd, ft_strlen(pwd));
			write(1, "\n", 1);
		}
	}
	return (EXIT_FAILURE);
}
