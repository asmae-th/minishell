/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:58:51 by atahtouh          #+#    #+#             */
/*   Updated: 2025/01/02 03:00:43 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	bubble_sort(char **array)
{
	int		size;
	char	*tmp;
	int		i;
	int		j;

	size = 0;
	while (array[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (f_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	handle_array_element(t_envp *tmp, char **array, int i)
{
	char	*join1;

	if (!tmp->val)
	{
		array[i] = ft_strdup(tmp->var);
		if (!array[i])
			return (free_arr(array), 0);
	}
	else
	{
		join1 = ft_strjoin(tmp->var, "=");
		if (!join1)
			return (free_arr(array), 0);
		array[i] = ft_strjoin(join1, tmp->val);
		free(join1);
		if (!array[i])
			return (free_arr(array), 0);
	}
	return (1);
}

int	fill_array(t_envp *tmp, char **array)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (!handle_array_element(tmp, array, i))
			return (0);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**array_join(t_envp **envp)
{
	char	**array;
	t_envp	*tmp;
	int		len;

	if (!envp)
		return (NULL);
	tmp = *envp;
	len = size_list(envp);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	if (!fill_array(tmp, array))
		return (NULL);
	return (array);
}
