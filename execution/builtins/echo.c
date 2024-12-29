/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:30 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 23:26:39 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
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

void	ft_echo(t_final_cmd *cmd)
{
	int	i;
	int	newline;

	if (!cmd || !cmd->arr[1]) // Vérifie s'il n'y a pas d'arguments
	{
		write(1, "\n", 1); // Affiche juste une nouvelle ligne
		return ;
	}
	i = 1;
	newline = 1;
	while (cmd->arr[i] && is_n_option(cmd->arr[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->arr[i])
	{
		printf("%s", cmd->arr[i]);
		if (cmd->arr[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
