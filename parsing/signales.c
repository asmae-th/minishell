/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signales.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:46:54 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 21:41:15 by atahtouh         ###   ########.fr       */
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

void	signal_handler(int status)
{
	if (status == SIGINT)
	{
		ft_setter(130, 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_delet_herdoc(void)
{
	char	*file_name;
	int		i;
	char	*itoa;

	i = 0;
	while (1)
	{
		itoa = ft_itoa(i);
		file_name = ft_strjoin("herdoc ", itoa);
		free(itoa);
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
