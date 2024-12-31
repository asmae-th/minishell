/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:23:59 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 15:30:03 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ls_new;
	t_list	*ls_tmp;

	if (!lst || !f || !del)
		return (NULL);
	ls_new = NULL;
	while (lst)
	{
		ls_tmp = ft_lstnew(f(lst->content));
		if (!ls_tmp)
		{
			ft_lstclear (&ls_new, del);
			return (NULL);
		}
		ft_lstadd_back(&ls_new, ls_tmp);
		lst = lst->next;
	}
	return (ls_new);
}
