/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:55:15 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 15:13:19 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	close_std(void)
{
	close_file_descriptors(3);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
}

int	ft_exit(t_final_cmd *cmd)
{
	int	exit_code;

	printf("exit\n");
	if (!cmd->arr[1])
	{
		ft_free_final_cmd(&cmd);
		close_std();
		exit(0);
	}
	if (cmd->arr[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (EXIT_FAILURE);
	}
	exit_code = f_atoi(cmd->arr[1]);
	if (exit_code == 0 && cmd->arr[1][0] != '0')
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		ft_free_final_cmd(&cmd);
		close_std();
		exit(255);
	}
	ft_free_final_cmd(&cmd);
	close_std();
	exit(exit_code);
}
