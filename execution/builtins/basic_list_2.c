/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:19:51 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 21:57:33 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	size_list(t_envp **envp)
{
	int		i;
	t_envp	*tmp;

	i = 0;
	tmp = *envp;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	plus_egal(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	free_export(t_envp *newnode)
{
	free(newnode->var);
	free(newnode->val);
	if (newnode->env)
		free(newnode->env);
	free(newnode);
}

void	default_env(t_envp **env)
{
	add_noeud(env, create_noeud("PATH=/home/atahtouh/bin:/usr/local/sbin:\
			/usr/local/bin:/usr/sbin:/usr/bin:/sbin:\
			/bin:/usr/games:/usr/local/games:/snap/bin"));
	add_noeud(env, create_noeud("_=/usr/bin/env"));
	add_noeud(env, create_noeud("OLDPWD"));
	add_noeud(env, create_noeud("PWD\
			=/home/atahtouh/Desktop/last_oneeeeeeeeeee"));
	add_noeud(env, create_noeud("SHLVL=1"));
}
