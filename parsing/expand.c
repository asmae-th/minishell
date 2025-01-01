/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:10:23 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 11:38:25 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	get_prev(t_token *token)
{
	t_token	*tmp;
	int i;
	int j;

	if (!token)
		return (0);
	i = 0;
	j = 0;
	tmp = token->prev;
	while (tmp)
	{
		if(tmp->type == A_SPACE)
			i++;
		if(tmp->type == HERE_DOC)
		{
			j = 5;
			break;
		}
		tmp = tmp->prev;
	}
	if (i == 1 && j == 5)
		return (1);
	return (0);
	
}

char	*ft_remplace_var(char *value, t_envp **env)
{
	t_envp	*tmp;
	char	*result;

	tmp = (*env)->next;
	while (tmp)
	{
		if (!ft_strcmp(value + 1, tmp->var))
		{
			free(value);
			result = ft_strndup(tmp->val, ft_strlen(tmp->val));
			return (result);
		}
		tmp = tmp->next;
	}
	free(value);
	return (ft_strndup("", ft_strlen("")));
}

int	ft_strchr1(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

// Implémentation de remplace_node
void	remplace_node(t_token **old_token, char **new_values)
{
    t_token	*current;
	int		i;

	current = *old_token;
    // On parcourt les nœuds pour trouver celui à remplacer
    while (current)
	{
        if (current->type == ENV_VAR || current->type == SPECIAL_VAR)
		{
            // On remplace le nœud actuel par les nouveaux nœuds
			i = 0;
            while (new_values[i] != NULL)
			{
                t_token *new_token = create_token(new_values[i], NEW_TYPE, NORMAL);
                add_token(old_token, new_token);
				i++;
            }
            // Suppression du nœud à remplacer
            if (current->prev)
			{
                current->prev->next = current->next; // Relier le précédent au suivant
            }
			else
			{
                *old_token = current->next; // Si c'est le premier nœud
            }
            if (current->next)
			{
                current->next->prev = current->prev; // Relier le suivant au précédent
            }
            // Libérer le nœud actuel
            free(current->value);
            free(current);
            return; // Sortir après le remplacement
        }
        current = current->next; // Passer au nœud suivant
    }
}

void	ft_expand(t_token **token, t_envp **env)
{
	t_token	*tmp_token;
	// t_token	*tmp_prev;

	tmp_token = *token;
	while (tmp_token)
	{
		if (tmp_token->type == ENV_VAR || tmp_token->type == SPECIAL_VAR)
		{
			if (tmp_token->prev != NULL)
			{
				// tmp_prev = get_prev(tmp_token);
				if (get_prev(tmp_token))
				{
					tmp_token->type = CMD;
					tmp_token = tmp_token->next;
					continue ;
				}
			}
			tmp_token->value = ft_remplace_var(tmp_token->value, env);
			if (ft_strchr1(tmp_token->value))
			{
				char **ptr;
				ptr = ft_split(tmp_token->value, ' ');
				remplace_node(token, ptr);//ajouter des nouedes au chaque nouede la valuer est ptr[i] et suprime la noude a remplacer
				free(ptr);
				tmp_token = *token;
				continue;
			}
			else
				tmp_token->type = CMD;
		}
		tmp_token = tmp_token->next;
	}
}
