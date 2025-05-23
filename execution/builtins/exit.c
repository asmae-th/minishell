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

void	cleanup_and_close(t_final_cmd **cmd)
{
	ft_free_final_cmd(cmd);
	close_std();
}

void	free_clean_exit(t_final_cmd *cmd, t_envp **envp, int exit_status)
{
	cleanup_and_close(&cmd);
	free_list(*envp);
	exit(exit_status);
}

long long	ft_exit(t_final_cmd *cmd, t_envp **envp)
{
	long long	exit_code;

	if (!cmd->next)
		write(1, "exit\n", 5);
	if (!cmd->arr[1])
		free_clean_exit(cmd, envp, 0);
	if (cmd->arr[2] && f_allnum(cmd->arr[1]) && f_allpha(cmd->arr[2]))
		return (write(2, "exit: too many arguments\n", 25), EXIT_FAILURE);
	if (cmd->arr[2] && f_allpha(cmd->arr[1]) && f_allnum(cmd->arr[2]))
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		free_clean_exit(cmd, envp, 2);
	}
	exit_code = f_atoi(cmd->arr[1]);
	if (exit_code == -1)
	{
		printf("exit: %s: numeric argument required\n", cmd->arr[1]);
		free_clean_exit(cmd, envp, 2);
	}
	free_list(*envp);
	cleanup_and_close(&cmd);
	rl_clear_history();
	clear_history();
	exit(exit_code);
}
