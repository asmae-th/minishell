/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:12 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 03:20:44 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	ft_envp(t_envp **envp, t_final_cmd *cmd)
{
	t_envp	*tmp;

	if (cmd->arr[1])
	{
		perror("env");
		return (127);
	}
	tmp = *envp;
	while (tmp)
	{
		if (tmp->var && tmp->val)
			printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
	return (OK);
}
