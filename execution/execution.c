/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:52:17 by feljourb          #+#    #+#             */
/*   Updated: 2025/01/09 16:59:23 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

char	*path_trouve(t_final_cmd *cmd, t_envp **env)
{
	char	*path;

	if (!cmd || !cmd->arr || !cmd->arr[0])
		return (NULL);
	path = NULL;
	if (cmd->arr[0][0] == '/' || cmd->arr[0][0] == '.')
		path = cmd->arr[0];
	else
		path = find_executable(cmd->arr[0], env);
	return (path);
}

int	prepare_and_execute(t_envp **envp, t_final_cmd *cmd)
{
	char	*path;

	path = path_trouve(cmd, envp);
	if (!path)
	{
		printf("%s : commande not found\n", cmd->arr[0]);
		return (ft_setter(127, 1));
	}
	if (is_directory(path))
	{
		printf("%s: is a directory\n", path);
		if (path != cmd->arr[0])
			free(path);
		return (ft_setter(126, 1));
	}
	execute_command_simple(path, cmd, envp);
	if (path != cmd->arr[0])
		free(path);
	return (0);
}

void	execute_command(t_final_cmd *cmd, t_envp **envp)
{
	if (cmd && cmd->next == NULL && builtins(cmd, envp) == 0)
		return ;
	if (cmd->next)
		pipeline(cmd, envp);
	else
		prepare_and_execute(envp, cmd);
}

int	analyse_cmd(t_final_cmd	*cmd)
{
	if (cmd == NULL)
	{
		signal(SIGINT, signal_handler);
		if (dup2(STDIN_FILENO, open(ttyname(2), O_RDONLY)) == -1)
			printf("eror\n");
		return (1);
	}
	return (0);
}

void	execution(t_final_cmd *cmd, t_envp **envp)
{
	if (analyse_cmd(cmd) || (!cmd->arr) || (!cmd->arr[0]))
		return ;
	execute_command(cmd, envp);
	close_file_descriptors(3);
}
