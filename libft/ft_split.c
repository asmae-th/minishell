/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:33:47 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/01 11:37:34 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
			j++;
		while (s[j] && s[j] == c)
			j++;
		i++;
	}
	return (i);
}

static int	ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		len;
	int		j;

	if (!s)
		return (0);
	len = ft_count(s, c);
	ptr = (char **)malloc((len + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	j = 0;
	while (*s && j < len)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			ptr[j] = ft_substr(s, 0, ft_len(s, c));
			j++;
		}
		while (*s && *s != c)
			s++;
	}
	ptr[j] = NULL;
	return (ptr);
}
