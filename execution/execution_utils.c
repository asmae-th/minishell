/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 00:47:52 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 01:14:52 by feljourb         ###   ########.fr       */
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
		{
			free_arr(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	free_arr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*find_executable(char *cmd)
{
	char *path = getenv("PATH");
	if (!path)
		return (NULL);
	char **directories = ft_split(path, ':');
	char *full_path = NULL;
	int 	i = 0;
	while (directories[i])
	{
		full_path = ft_strjoin(directories[i], "/");
		char *temp_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(temp_path, X_OK) == 0)
		{
			free_arr(directories);
			return (temp_path);
		}
		free(temp_path);
		i++;
	}
	free_arr(directories);
	return (NULL);
}

