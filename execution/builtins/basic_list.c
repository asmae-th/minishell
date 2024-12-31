/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:18:06 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/31 15:25:20 by atahtouh         ###   ########.fr       */
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

void	init_struct(t_envp **new_noeud)
{
	(*new_noeud)->env = NULL;
	(*new_noeud)->var = NULL;
	(*new_noeud)->val = NULL;
	(*new_noeud)->join = NULL;
	(*new_noeud)->next = NULL;
}

void	set_var_val_env(t_envp *new_noeud, char *str, size_t indice)
{
	new_noeud->var = ft_substr(str, 0, indice);
	new_noeud->val = ft_substr(str, indice + 1, ft_strlen(str) - indice);
	new_noeud->env = ft_strdup(str);
}

t_envp	*create_noeud(char *str)
{
	t_envp	*new_noeud;
	size_t	indice;

	new_noeud = malloc(sizeof(t_envp));
	if (!new_noeud)
		return (NULL);
	init_struct(&new_noeud);
	indice = egale_indice(str);
	if (plus_egal(str) == 1)
	{
		new_noeud->join = ft_substr(str, 0, indice + 1);
		new_noeud->var = ft_substr(str, 0, indice - 1);
		new_noeud->val = ft_substr(str, indice + 1, ft_strlen(str) - indice);
		new_noeud->env = ft_strdup(str);
		return (new_noeud);
	}
	if (indice == ft_strlen(str))
	{
		new_noeud->var = ft_strdup(str);
		new_noeud->env = ft_strdup(str);
		return (new_noeud);
	}
	set_var_val_env(new_noeud, str, indice);
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
