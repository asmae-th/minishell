/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:12 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/17 00:16:07 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

// void	ft_envp(t_envp *envp)
// {
// 	t_envp	*tmp;

// 	tmp = envp;
// 	while (tmp && tmp->val != NULL)
// 	{
// 		printf("%s=%s\n", tmp->var, tmp->val);
// 		tmp = tmp->next;
// 	}
// }

void	ft_envp(t_envp *envp)
{
    t_envp *tmp = envp;

    while (tmp)
	{
        if (tmp->var && tmp->val) // N'affiche que les variables avec une valeur
            printf("%s=%s\n", tmp->var, tmp->val);
        tmp = tmp->next;
    }
}
