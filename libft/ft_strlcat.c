/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:39:00 by atahtouh          #+#    #+#             */
/*   Updated: 2023/11/14 19:03:35 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s;
	size_t	d;

	i = 0;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (dstsize == 0 || dstsize <= d)
		return (s + dstsize);
	while (src[i] != '\0' && i < dstsize - d - 1)
	{
		dst[d + i] = src [i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}
