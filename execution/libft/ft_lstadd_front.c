/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:01:35 by feljourb          #+#    #+#             */
/*   Updated: 2024/03/18 00:15:29 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
    if(*lst == NULL)
    {
        *lst = new;
    }
    else
    {
       new->next = *lst;
        *lst = new;
    }
}
int main()
{
    t_list *head = NULL; 
    
    t_list *N3 = ft_lstnew("hajar");
    t_list *N1 = ft_lstnew("fati");
    t_list *N2 = ft_lstnew("asmae");
    t_list *n5 = ft_lstnew("zobida");
    ft_lstadd_front(&head, N3);
    ft_lstadd_back(&head, n5);
    ft_lstadd_front(&head, N1);
    ft_lstadd_front(&head, N2);
    printf("%s\n",ft_lstlast(head)->content);
    while (head)
    {
         printf("%s\n",head->content);
         head = head->next;
    }
}