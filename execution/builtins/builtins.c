/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:59 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/17 01:21:31 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	builtins(char **av, t_envp **envp)
{
	if (!av || !av[0])
		return (1);
	if (f_strcmp(av[0], "echo") == 0)
		ft_echo(av);
	else if (f_strcmp(av[0], "cd") == 0)
		ft_cd(av);
	else if (f_strcmp(av[0], "pwd") == 0)
		ft_pwd();
	else if (f_strcmp(av[0], "exit") == 0)
		ft_exit(av);
	else if (f_strcmp(av[0], "env") == 0)
		ft_envp(*envp);
	else if (f_strcmp(av[0], "unset") == 0)
		ft_unset(envp, av);
	else if (f_strcmp(av[0], "export") == 0)
		ft_export(envp, av);
	else
		return (1);
	return (0);
}
