/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:49:35 by feljourb          #+#    #+#             */
/*   Updated: 2024/03/16 10:05:16 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
if (*lst == NULL)
{
    *lst = new;
}
    
    t_list *temp= *lst;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;
}