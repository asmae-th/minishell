/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:55:15 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/28 23:29:50 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	ft_exit(t_final_cmd *cmd)
{
	int	exit_code;

	printf("exit\n");
	if (!cmd->arr[1])
		exit(0);
	if (cmd->arr[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	exit_code = f_atoi(cmd->arr[1]);
	if (exit_code == 0 && cmd->arr[1][0] != '0')
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		exit(255);// 255 Utilisé pour des erreurs non spécifiques ou graves, comme des arguments invalides ou des erreurs internes
	}
	exit(exit_code);
}
