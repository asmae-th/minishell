/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:44:23 by feljourb          #+#    #+#             */
/*   Updated: 2023/12/05 11:42:59 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	cc;
	int				i;

	cc = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	if (str[i] == cc)
		return ((char *)str + i);
	return (NULL);
}
