/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:14:45 by feljourb          #+#    #+#             */
/*   Updated: 2024/03/16 08:40:05 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstsize(t_list *lst)
{
	int i;

	i = 1;
	if (lst == NULL)
		return(0);
	t_list *temp = lst; // pour garder la htete de list
	while (temp->next != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
