/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:23:45 by feljourb          #+#    #+#             */
/*   Updated: 2023/12/03 19:12:21 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	f;
	size_t	l;
	char	*str;

	f = 0;
	if (!s1 || !set)
		return (NULL);
	l = ft_strlen(s1);
	while (s1[f] && ft_strchr(set, s1[f]))
		f++;
	while (l > f && ft_strchr(set, s1[l - 1]))
		l--;
	str = ft_substr(s1, f, (l - f));
	return (str);
}
