/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:58 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/25 22:49:40 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #getcwd: récupère le chemin absolu du répertoire de travail actuel .

#include "../../include/execution.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // Alloue dynamiquement la mémoire nécessaire
	if (cwd != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
}
