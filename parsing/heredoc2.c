/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:17:12 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 14:11:09 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*get_env_value(char *var_name, t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->var, var_name) == 0)
			return (ft_strdup(current->val));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*process_env_variable(char **tmp, t_envp **env, char *result)
{
	char	*var_name;
	char	*var_value;
	int		j;

	result = ft_strjoin(result, ft_substr(*tmp, 0, 0));
	(*tmp)++;
	j = 0;
	while ((*tmp)[j] && (ft_isalnum((*tmp)[j]) || (*tmp)[j] == '_'))
		j++;
	var_name = ft_substr(*tmp, 0, j);
	*tmp += j;
	var_value = get_env_value(var_name, env);
	free(var_name);
	result = ft_strjoin(result, var_value);
	free(var_value);
	return (result);
}

char	*process_plain_text(char **tmp, char *result)
{
	int		i;
	char	*start;

	i = 0;
	start = *tmp;
	while ((*tmp)[i] && (*tmp)[i] != '$')
		i++;
	result = ft_strjoin(result, ft_substr(start, 0, i));
	*tmp += i;
	return (result);
}

char	*heredoc_expand(char **line, t_envp **env)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	tmp = *line;
	while (tmp && *tmp)
	{
		if (*tmp == '$')
			result = process_env_variable(&tmp, env, result);
		else
			result = process_plain_text(&tmp, result);
	}
	free(*line);
	*line = result;
	return (result);
}
