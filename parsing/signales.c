/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signales.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:46:54 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 17:21:32 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_setter(int code, int mode)
{
	static int	exit_status;

	if (mode)
		exit_status = code;
	return (exit_status);
}

void	seg_handler_c(int status)
{
	if (status == SIGINT)
	{
		ft_setter(1, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, seg_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_delet_herdoc(void)
{
	char	*file_name;
	int		i;

	i = 0;
	while (1)
	{
		file_name = ft_strjoin("herdoc ", ft_itoa(i));
		if (!file_name)
			break ;
		if (unlink(file_name) == -1)
		{
			free(file_name);
			break ;
		}
		free(file_name);
		i++;
	}
}
