/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:55:15 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/01 21:52:42 by atahtouh         ###   ########.fr       */
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

int	f_allnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90)
			|| (str[i] >= 97 && str[i] <= 122)
			|| (str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int	f_allpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90)
			|| (str[i] >= 97 && str[i] <= 122))
			return (1);
		i++;
	}
	return (0);
}

void	cleanup_and_close(t_final_cmd **cmd)
{
	ft_free_final_cmd(cmd);
	close_std();
}

long long	ft_exit(t_final_cmd *cmd)
{
	long long	exit_code;

	if (!cmd->arr[1])
	{
		cleanup_and_close(&cmd);
		exit(0);
	}
	if (cmd->arr[2] && f_allnum(cmd->arr[1]) && f_allpha(cmd->arr[2]))
		return (write(2, "exit: too many arguments\n", 25), EXIT_FAILURE);
	if (cmd->arr[2] && f_allpha(cmd->arr[1]) && f_allnum(cmd->arr[2]))
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		exit(2);
	}
	exit_code = f_atoi(cmd->arr[1]);
	if (exit_code == -1)
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		cleanup_and_close(&cmd);
		exit(2);
	}
	cleanup_and_close(&cmd);
	clear_history();
	exit(exit_code);
}
