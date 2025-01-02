/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:15:38 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/02 01:55:12 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	free_list(t_envp *list)
{
	t_envp	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->env);
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void	delete_first_noeud(t_envp **envp, t_envp *to_delete)
{
	t_envp	*tmp;

	if (!envp || !*envp || !to_delete)
		return ;
	tmp = *envp;
	if (f_strcmp(tmp->var, to_delete->var) == 0)
	{
		*envp = tmp->next;
		free_noeud(tmp);
		return ;
	}
}

void	free_noeud(t_envp *tmp)
{
	if (!tmp)
		return ;
	free(tmp->var);
	free(tmp->env);
	free(tmp->val);
	free(tmp);
}

void	delete_noeud(t_envp **envp, t_envp *to_delete)
{
	t_envp	*tmp;
	t_envp	*prev;

	if (!envp || !*envp || !to_delete)
		return ;
	tmp = *envp;
	prev = NULL;
	if (f_strcmp(tmp->var, to_delete->var) == 0)
	{
		delete_first_noeud(envp, to_delete);
		return ;
	}
	while (tmp)
	{
		if (f_strcmp(tmp->var, to_delete->var) == 0)
		{
			prev->next = tmp->next;
			free_noeud(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	copie_env_list(t_envp **env, char **envp)
{
	int	i;

	i = 0;
	if (!envp
		|| ft_strcmp(envp[0], "PWD=/home/atahtouh/Desktop/minishell2") == 0)
	{
		default_env(env);
		return ;
	}
	while (envp[i])
	{
		add_noeud(env, create_noeud(envp[i]));
		i++;
	}
}
