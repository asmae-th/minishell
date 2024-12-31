/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:30 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 15:12:52 by atahtouh         ###   ########.fr       */
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

int	ft_echo(t_final_cmd *cmd)
{
	int	i;
	int	newline;

	if (!cmd || !cmd->arr[1])
	{
		write(1, "\n", 1);
		return (EXIT_FAILURE);
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
	return (OK);
}
