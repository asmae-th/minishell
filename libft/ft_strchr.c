/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:59:35 by atahtouh          #+#    #+#             */
/*   Updated: 2024/11/26 16:46:28 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(char *str, int c)
{
	char	s;
	int		i;

	i = 0;
	s = (char )c;
	while (str[i] != '\0')
	{
		if (str[i] == s)
			return (str + i);
		i++;
	}
	if (s == '\0')
		return (str + i);
	return (NULL);
}
