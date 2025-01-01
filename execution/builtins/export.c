/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:03 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 21:59:31 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	update_envp_value(t_envp *tmp, t_envp *new_node)
{
	free(tmp->val);
	tmp->val = ft_strdup(new_node->val);
}

void	add_or_apdate_envp(t_envp **envp, t_envp *new_node)
{
	t_envp	*tmp;
	char	*str;

	tmp = (*envp);
	while (tmp)
	{
		if (f_strcmp(tmp->var, new_node->var) == 0)
		{
			if (new_node->join && plus_egal(new_node->join) == 1)
			{
				str = tmp->val;
				tmp->val = ft_strjoin(str, new_node->val);
				free(str);
				free(new_node->join);
			}
			else
				update_envp_value(tmp, new_node);
			free_export(new_node);
			return ;
		}
		tmp = tmp->next;
	}
	add_noeud(envp, new_node);
	if (new_node->join)
		free(new_node->join);
}

void	print_export(t_envp **envp)
{
	char	**array;
	int		i;

	array = array_join(envp);
	if (!array)
		return ;
	bubble_sort(array);
	i = 0;
	while (array[i])
	{
		printf("declare -x \"%s\"\n", array[i]);
		i++;
	}
	free_arr(array);
}

int	ft_export(t_envp **envp, t_final_cmd *cmd)
{
	t_envp	*newnode;
	int		i;

	i = 1;
	if (!cmd->arr[1])
		return (print_export(envp), OK);
	while (cmd->arr[i])
	{
		newnode = create_noeud(cmd->arr[i]);
		if (!newnode)
			return (EXIT_FAILURE);
		if (f_isalpha(newnode->var))
		{
			printf("export: `%s`: not a valid identifier\n", cmd->arr[i]);
			free_export(newnode);
			return (EXIT_FAILURE);
		}
		else
			add_or_apdate_envp(envp, newnode);
		i++;
	}
	return (OK);
}
