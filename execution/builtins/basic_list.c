/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:18:06 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/17 00:27:00 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

size_t	egale_indice(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	plus_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_envp	*create_noeud(char *str)
{
	t_envp	*new_noeud;
	size_t	indice;

	new_noeud = malloc(sizeof(t_envp));
	if (!new_noeud)
		return (NULL);
	indice = egale_indice(str);
	if (plus_egal(str) == 1)
	{
		new_noeud->join = ft_substr(str, 0, indice + 1);
		new_noeud->var = ft_substr(str, 0, indice - 1);
		new_noeud->val = ft_substr(str, indice + 1, ft_strlen(str) - indice);
		new_noeud->next = NULL;
		return (new_noeud);
	} //SHLVL=1
	if (indice == ft_strlen(str))
	{
		new_noeud->var = ft_strdup(str);
		new_noeud->val = NULL;
		new_noeud->next = NULL;
		return (new_noeud);
	}
	new_noeud->var = ft_substr(str, 0, indice);
	new_noeud->val = ft_substr(str, indice + 1, ft_strlen(str) - indice);
	new_noeud->env = ft_strdup(str); // -> env : pour contient tous le str 
	new_noeud->next = NULL ;
	return (new_noeud);
}

void	add_noeud(t_envp **head, t_envp *newNode)
{
	t_envp	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = newNode;
}

void	free_list(t_envp *list)
{
	t_envp	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->env);
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void	delete_noeud(t_envp **envp, t_envp *to_delete)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = *envp;
	prev = NULL;
	if (!*envp || !to_delete)
		return ;
	if (f_strcmp(tmp->var, to_delete->var) == 0)
	{
		*envp = tmp->next;
		free(tmp->var);
		free(tmp->env);
		free(tmp->val);
		free(tmp);
		return ;
	}
	while (tmp)
	{
		if (f_strcmp(tmp->var, to_delete->var) == 0)
		{
			prev->next = tmp->next;
			free(tmp->var);
			free(tmp->env);
			free(tmp->val);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	copie_env_list(t_envp **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_noeud(env, create_noeud(envp[i]));
		i++;
	}
}

int	size_list(t_envp *envp)
{
	int		i;
	t_envp	*tmp;

	i = 0;
	tmp = envp;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
