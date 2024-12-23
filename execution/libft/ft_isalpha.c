/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:22:52 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/01 22:40:33 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(char *str)
{
	int i;

	i = 0;
	if (!(str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
		return (1); // Erreur si le premier caractère est invalide
	// int	len = ft_strlen(str) - 1;
	while (str[i])
	{
		if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || 
              (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) // str[len] == '+'
			return (1); // Erreur si un caractère est invalide
		i++;
	}
	return (0); // Tout est valide
}
