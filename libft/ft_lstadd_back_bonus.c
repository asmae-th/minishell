/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:56:19 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 15:29:52 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ls;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ls = *lst;
		while (ls->next != NULL)
		{
			ls = ls->next;
		}
		ls->next = new;
	}
}
