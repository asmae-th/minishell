/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:00:37 by atahtouh          #+#    #+#             */
/*   Updated: 2023/11/19 15:49:00 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*new_s;
	size_t	size_s;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (0);
	str = (char *)s1;
	while (*str && ft_strchr((char *)set, *str))
		str++;
	size_s = ft_strlen((char *)str);
	if (i == size_s)
		return (ft_substr("", 0, size_s));
	while (size_s && ft_strchr((char *)set, str[size_s]))
		size_s--;
	new_s = ft_substr(str, 0, size_s + 1);
	return (new_s);
}
