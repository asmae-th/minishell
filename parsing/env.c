/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:10:43 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 15:56:53 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_indice(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_env	*ft_init_env(t_env **new_env, char **env)
{
	(*new_env) = malloc(sizeof(t_env));
	if (!(*new_env))
		return (NULL);
	(*new_env)->i_env = env;
	(*new_env)->var = NULL;
	(*new_env)->val = NULL;
	(*new_env)->next = NULL;
	(*new_env)->prev = NULL;
	return ((*new_env));
}

t_env	*creat_env(char *str)
{
	t_env	*new_noud;
	int		indice_equal;

	new_noud = malloc(sizeof(t_env));
	if (!new_noud)
		return (NULL);
	indice_equal = ft_indice(str, '=');
	if (indice_equal != -1)
	{
		new_noud->var = ft_substr(str, 0, indice_equal);
		new_noud->val = ft_substr(str, indice_equal + 1,
				ft_strlen(str) - indice_equal);
	}
	else
	{
		new_noud->var = ft_substr(str, 0, ft_strlen(str));
		new_noud->val = NULL;
	}
	new_noud->i_env = NULL;
	new_noud->prev = NULL;
	new_noud->next = NULL;
	return (new_noud);
}

void	add_env(t_env **new_env, t_env *new_noud)
{
	t_env	*tmp;

	if (!(*new_env))
		(*new_env) = new_noud;
	else
	{
		tmp = *new_env;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_noud;
		new_noud->prev = tmp;
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

t_env	*ft_env(char	**env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = NULL;
	while (env[i])
	{
		add_env(&new_env, creat_env(env[i]));
		i++;
	}
	return (new_env);
}
