/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:38:37 by atahtouh          #+#    #+#             */
/*   Updated: 2023/11/21 09:18:07 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	n;
	char	*ptr;

	n = nmemb * size;
	ptr = (char *)malloc(n * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_bzero((void *)ptr, n);
	return ((void *)ptr);
}
