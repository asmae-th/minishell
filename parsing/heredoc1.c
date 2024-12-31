/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:19:42 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 14:24:12 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	here_signal(int heredoc)
{
	if (heredoc == SIGINT)
	{
		ft_setter(1, 1);
		if (dup2(STDERR_FILENO, 0) == -1)
			printf("error\n");
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	ft_printf(char *redline, int line, char *file)
{
	if (!redline)
	{
		printf("warning: here-document at line %d ", line);
		printf("delimited by end-of-file (wanted `%s')\n", file);
	}
}
