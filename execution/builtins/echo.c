/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:30 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/24 13:25:35 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **av)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (av[i] && is_n_option(av[i]))
	{
		newline = 0;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
