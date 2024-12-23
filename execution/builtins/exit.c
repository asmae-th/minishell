/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:55:15 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/15 18:43:19 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	ft_exit(char **av)
{
	int	exit_code;

	if (!av[1])
		exit(0);
	if (av[2])
	{
		perror("to many arguments");
		return ;
	}
	exit_code = f_atoi(av[1]);
	if (exit_code == 0 && av[1][0] != '0')
	{
		printf("exit: %s: numeric argument required\n", av[1]);
		exit(255);
		// 255 Utilisé pour des erreurs non spécifiques ou graves, comme des arguments invalides ou des erreurs internes
	}
	exit(exit_code);
}
