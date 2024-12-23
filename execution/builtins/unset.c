/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:08 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/15 17:33:41 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	ft_unset(t_envp **envp, char **av)
{
	t_envp	*to_unset;

	if (!av[1] || ft_strchr(av[1], '='))
		return ;
	to_unset = create_noeud(av[1]);
	delete_noeud(envp, to_unset);
	free(to_unset->var);
	free(to_unset->val);
	free(to_unset->env);
	free(to_unset);
}
