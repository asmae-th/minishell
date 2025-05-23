/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 00:47:52 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 14:50:14 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	**copie_list_in_array(t_envp **envp)
{
	char	**array;
	t_envp	*tmp;
	int		i;
	int		len;

	if (!envp)
		return (NULL);
	i = 0;
	tmp = *envp;
	len = size_list(envp);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	while (tmp)
	{
		array[i] = ft_strdup(tmp->env);
		if (!array[i])
			return (free_arr(array), NULL);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*get_path(t_envp **env)
{
	t_envp	*tmp;
	char	*path;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PATH") == 0)
		{
			path = tmp->val;
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_executable(char *cmd, t_envp **env)
{
	char	*path;
	char	*temp_path;
	char	*full_path;
	char	**directories;
	int		i;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	path = get_path(env);
	if (!path)
		return (NULL);
	directories = ft_split(path, ':');
	full_path = NULL;
	i = 0;
	while (directories[i])
	{
		full_path = ft_strjoin(directories[i], "/");
		temp_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(temp_path, X_OK) == 0)
			return (free_arr(directories), temp_path);
		free(temp_path);
		i++;
	}
	return (free_arr(directories), NULL);
}
