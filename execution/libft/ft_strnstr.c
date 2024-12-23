/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:43:30 by feljourb          #+#    #+#             */
/*   Updated: 2023/12/03 19:18:24 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)(big));
	while (big[i] && i < n)
	{
		j = 0;
		while (little[j] && i + j < n)
		{
			if (little[j] != big[i + j])
				break ;
			j++;
		}
		if (little[j] == '\0')
			return ((char *)(&big[i]));
		i++;
	}
	return (NULL);
}
