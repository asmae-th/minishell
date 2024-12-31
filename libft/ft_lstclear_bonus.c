/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:02:10 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 15:29:54 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ls;
	t_list	*lsnext;

	if (!lst || !del)
		return ;
	ls = *lst;
	while (ls != NULL)
	{
		lsnext = ls->next;
		del(ls->content);
		free(ls);
		ls = lsnext;
	}
	*lst = NULL;
}
