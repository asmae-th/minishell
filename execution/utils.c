/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:29:37 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/15 17:40:05 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	f_atoi(const char *str)
{
	int		i;
	long	result;
    int     sign;

	i = 0;
	result = 0;
    sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-') 
			sign *= -1;   
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || result > LONG_MAX || result < LONG_MIN)
		return (0);
	return (sign * result);
}

int	f_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	f_isalpha(char *str)
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