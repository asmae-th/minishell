/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:15:58 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/15 17:33:37 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #getcwd: récupère le chemin absolu du répertoire de travail actuel .

#include "../../include/execution.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}
