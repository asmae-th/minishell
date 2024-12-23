/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:25:02 by atahtouh          #+#    #+#             */
/*   Updated: 2023/11/16 13:49:41 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ls;

	if (lst == NULL)
		return (NULL);
	ls = lst;
	while (ls->next != NULL)
	{
		ls = ls->next;
	}
	return (ls);
}
