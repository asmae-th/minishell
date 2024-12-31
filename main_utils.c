/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:36:07 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 13:44:57 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	close_file_descriptors(int start_fd)
{
	struct stat	fd_stat;
	int			fd;

	while (start_fd < MAX_FD)
	{
		fd = start_fd;
		if (fstat(fd, &fd_stat) == 0)
			close(fd);
		start_fd++;
	}
}

void	history(char *str, size_t i, size_t len, int *state)
{
	*state = 0;
	if (i >= len || *state == 1)
		return ;
	if (str[i] == '\t')
		history(str, i + 1, len, state);
	else
	{
		*state = 1;
		return ;
	}
}
