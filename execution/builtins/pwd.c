/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:58 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 15:13:57 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #getcwd: récupère le chemin absolu du répertoire de travail actuel .

#include "../../include/execution.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
		return (OK);
	}
	else
	{
		perror("pwd");
		free(cwd);
	}
	return (EXIT_FAILURE);
}
