/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 00:30:21 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 00:31:52 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	handle_error(const char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

void	handle_cmd_not_found(const char *cmd)
{
	fprintf(stderr, "%s: command not found\n", cmd);
	exit(127);
}

void	handle_execve_error(char **env)
{
	perror("execve failed");
	free_arr(env);
	exit(1);
}
