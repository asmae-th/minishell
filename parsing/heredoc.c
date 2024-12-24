/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:41:46 by asmae             #+#    #+#             */
/*   Updated: 2024/12/24 11:04:58 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	signal_herdoc_handler(int heredoc)
{
	if (heredoc == SIGINT)
	{
		ft_setter(1, 1);
		if (dup2(STDERR_FILENO, 0) == -1)
		{
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	ft_signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_herdoc_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

char	*get_env_value(char *var_name, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->var, var_name) == 0)
			return (ft_strdup(current->val));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*heredoc_expand(char **line, t_env **env)
{
	char	*result;
	char	*tmp;
	char	*start;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;

	i = 0;
	result = ft_strdup("");
	tmp = *line;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '$')
		{
			result = ft_strjoin(result, ft_substr(tmp, 0, i));
			tmp += i + 1;
			j = 0;
			while (tmp[j] && (ft_isalnum(tmp[j]) || tmp[j] == '_'))
				j++;
			var_name = ft_substr(tmp, 0, j);
			tmp += j;
			var_value = get_env_value(var_name, env);
			free(var_name);
			result = ft_strjoin(result, var_value);
			free(var_value);
		}
		else
		{
			start = tmp;
			while (tmp[i] && tmp[i] != '$')
				i++;
			result = ft_strjoin(result, ft_substr(start, 0, i));
			tmp += i;
			i = 0;
		}
	}
	free(*line);
	*line = result;
	return (result);
}

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

char	*heredoc(char *file, int new_name, t_env **env, t_herdoc valid)
{
	char	*file_name;
	char	*redline;
	int		fd_heredoc;
	int		line;

	ft_signal_heredoc();
	file_name = ft_strjoin("herdoc ", ft_itoa(new_name));
	fd_heredoc = open(file_name, O_RDWR | O_CREAT, 0666);
	line = 0;
	while (1)
	{
		redline = readline("HEREDOC> ");
		line++;
		if (!redline)
			printf("warning: here-document at line %d\
				delimited by end-of-file (wanted `%s')\n", line, file);
		if (!redline || ft_strcmp(redline, file) == 0)
		{
			free(redline);
			break ;
		}
		if (ft_indice(redline, '$') != -1)
		{
			if (valid == FALS)
				redline = heredoc_expand(&redline, env);
		}
		write(fd_heredoc, redline, ft_strlen(redline));
		write(fd_heredoc, "\n", 1);
		free(redline);
		redline = NULL;
	}
	return (file_name);
}

void	ft_here_doc(t_tmp_cmd **cmd, t_env **env)
{
	t_tmp_cmd	*current;
	int			new_name;

	current = *cmd;
	new_name = 0;
	while (current)
	{
		if (current->f_type == HEREDOC_FILE)
		{
			current->value = heredoc(current->value, new_name,
					env, current->valid);
			new_name++;
		}
		current = current->next;
	}
}
