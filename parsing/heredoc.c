/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:41:46 by asmae             #+#    #+#             */
/*   Updated: 2024/12/29 19:58:10 by atahtouh         ###   ########.fr       */
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

void	ft_printf(char *redline, int line, char *file)
{
	if (!redline)
	{
		printf("warning: here-document at line %d", line);
		printf("delimited by end-of-file (wanted `%s')\n", file);
	}
}

char *heredoc(char *file, int new_name, t_envp **env, t_herdoc valid)
{
	char *file_name;
	char *redline;
	int fd_heredoc;
	int line;
	int pid;
	int status;

	file_name = ft_strjoin("herdoc ", ft_itoa(new_name));
	fd_heredoc = open(file_name, O_RDWR | O_CREAT, 0666);
	line = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();//if failed protection
	if (pid == 0)  // Child process
	{
		ft_signal_heredoc();  // Set up signal handling for the child process
		while (1)
		{
			redline = readline("HEREDOC> ");
			line++;
			ft_printf(redline, line, file);

			if (!redline || ft_strcmp(redline, file) == 0)
			{
				free(redline);
				break;
			}

			if (ft_indice(redline, '$') != -1)
				if (valid == FALS)
					redline = heredoc_expand(&redline, env);

			redline = ft_write(redline, fd_heredoc);
		}
		close(fd_heredoc);
		exit(0);  // Exit the child process gracefully
	}
	else  // Parent process
	{
		if (waitpid(pid, &status, 0) == -1) // Wait for the child process to finish
		{
			perror("waitpid failed");
			exit(1);
		}

		if (WIFEXITED(status)) // Check if the child exited normally
			ft_setter(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))  // Check if the child was terminated by signal
			ft_setter(128 + WTERMSIG(status), 1);
	}
	return (file_name);
}
// char	*heredoc(char *file, int new_name, t_envp **env, t_herdoc valid)
// {
// 	char	*file_name;
// 	char	*redline;
// 	int		fd_heredoc;
// 	int		line;

// 	file_name = ft_strjoin("herdoc ", ft_itoa(new_name));
// 	fd_heredoc = open(file_name, O_RDWR | O_CREAT, 0666);
// 	line = 0;
// 	while (1)
// 	{
// 		ft_signal_heredoc();
// 		redline = readline("HEREDOC> ");
// 		line++;
// 		// ft_printf(redline, line, file);
// 		if (!redline)
// 		{
// 			printf("warning: here-document at line %d", line);
// 			printf("delimited by end-of-file (wanted `%s')\n", file);
// 			// break;
// 		}
// 		if (!redline || ft_strcmp(redline, file) == 0)
// 		{
// 			free(redline);
// 			break ;
// 		}
// 		if (ft_indice(redline, '$') != -1)
// 			if (valid == FALS)
// 				redline = heredoc_expand(&redline, env);
// 		redline = ft_write(redline, fd_heredoc);
// 	}
// 	return (file_name);
// }

void	ft_here_doc(t_tmp_cmd **cmd, t_envp **env)
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
