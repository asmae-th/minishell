/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:34:59 by feljourb          #+#    #+#             */
/*   Updated: 2024/03/14 17:19:50 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list *node;
    
    node = malloc(sizeof(t_list));
    if(!node)
        return(NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}
// int main()
// {
// 	t_list *Node = ft_lstnew("fati");
	
// 		while(Node != NULL)
// 		{
// 			printf("%s",Node->content);
// 				Node = Node->next;
// 		}
// }