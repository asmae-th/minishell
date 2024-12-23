/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:01 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/21 11:29:19 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;

	if(!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy (ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}
