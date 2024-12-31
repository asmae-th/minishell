/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:41:46 by asmae             #+#    #+#             */
/*   Updated: 2024/12/31 14:21:05 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_check_herdoc_quote(t_tmp_cmd **cmd)
{
	t_tmp_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->type == HERE_DOC && (tmp->next
				&& (tmp->next->state == IN_DQUOT
					|| tmp->next->state == IN_SQUOT)))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_write(char *readline, int fd)
{
	write(fd, readline, ft_strlen(readline));
	write(fd, "\n", 1);
	free(readline);
	return (NULL);
}

void	free_heredoc(char *file, char *new_name)
{
	free(file);
	free(new_name);
}

char	*heredoc(char *file, char *new_name, t_envp **env, t_herdoc valid)
{
	char	*file_name;
	char	*redline;
	int		fd_heredoc;
	int		line;

	file_name = ft_strjoin("herdoc ", new_name);
	fd_heredoc = open(file_name, O_RDWR | O_CREAT, 0666);
	line = 0;
	signal(SIGINT, here_signal);
	while (1)
	{
		redline = readline("HEREDOC> ");
		line++;
		ft_printf(redline, line, file);
		if (!redline || ft_strcmp(redline, file) == 0)
		{
			free(redline);
			break ;
		}
		if (ft_indice(redline, '$') != -1)
			if (valid == FALS)
				redline = heredoc_expand(&redline, env);
		redline = ft_write(redline, fd_heredoc);
	}
	return (free_heredoc(file, new_name), file_name);
}

int	ft_here_doc(t_tmp_cmd **cmd, t_envp **env)
{
	t_tmp_cmd	*current;
	int			new_name;

	current = *cmd;
	new_name = 0;
	while (current)
	{
		if (current->f_type == HEREDOC_FILE)
		{
			current->value = heredoc(current->value, ft_itoa(new_name),
					env, current->valid);
			if (!(ttyname(STDIN_FILENO)))
				return (404);
			new_name++;
		}
		current = current->next;
	}
	return (1);
}
