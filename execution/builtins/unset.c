/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:08 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 00:02:07 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	ft_unset(t_envp **envp, t_final_cmd *cmd)
{
	t_envp	*to_unset;
	int		i;

	i = 1;
	while (cmd->arr[i])
	{
		if (ft_strchr(cmd->arr[i], '='))//Vérification de la présence du caractère =
		{
			i++;
			continue ;
		}
		to_unset = create_noeud(cmd->arr[i]);
		if (!to_unset)
		{
			write(2, "unset: allocation error\n", 24);
			i++;
			continue ;
		}
		delete_noeud(envp, to_unset);
		free(to_unset->var);
		free(to_unset->val);
		free(to_unset->env);
		free(to_unset);
		i++;
	}
}
