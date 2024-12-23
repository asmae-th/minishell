/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:03 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/17 18:42:30 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	add_or_apdate_envp(t_envp **envp, t_envp *new_node)
{
	t_envp	*tmp;
	char	*str;

	tmp = (*envp);
	while (tmp->next)
	{
		if (f_strcmp(tmp->var, new_node->var) == 0)
		{
			if (plus_egal(new_node->join) == 1)
			{
				str = tmp->val;
				tmp->val = ft_strjoin(str, new_node->val);
				free(str);
				free(new_node->join);
			}
			else
			{
				free(tmp->val);
				tmp->val = ft_strdup(new_node->val);
			}
			free(new_node->var);
			free(new_node->val);
			free(new_node);
			return ;
		}
		tmp = tmp->next;
	}
	add_noeud(envp, new_node);
}

void	print_export(t_envp *envp)
{
	t_envp *tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->var)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	ft_export(t_envp **envp, char **av)
{
	t_envp *newNode;
	if (!av[1])
	{
		print_export(*envp);
		return ;
	}
	newNode = create_noeud(av[1]);
	if (f_isalpha(newNode->var))
	{
		perror("export: invalid identifier");
		return ;
	}
	add_or_apdate_envp(envp, newNode);
	// ft_envp(*envp);
}
