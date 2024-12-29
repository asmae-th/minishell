/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:19:51 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 23:20:52 by feljourb         ###   ########.fr       */
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
