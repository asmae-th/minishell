/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:10:23 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 12:24:44 by asmae            ###   ########.fr       */
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

// t_token	*get_prev(t_token *token)
// {
// 	t_token *tmp;
	
// 	tmp = token->prev;
// 	while (tmp && tmp->type == A_SPACE)
// 		tmp = tmp->prev;
// 	return (tmp);
// }

t_token	*get_prev(t_token *token)
{
	t_token *tmp;

	if (!token) // Vérifie si token est NULL
		return (NULL);

	tmp = token->prev; // Récupère le précédent
	while (tmp)
	{
		if (tmp->type != A_SPACE) // Arrête si le type n'est pas A_SPACE
			break;
		tmp = tmp->prev; // Passe au précédent
	}
	return (tmp); // Retourne le précédent valide ou NULL
}


char *ft_remplace_var(char *value, t_env **env)
{
	t_env *tmp;

	tmp = (*env)->next;
	while (tmp)
	{
		if(!ft_strcmp(value + 1, tmp->var))
		{
			// printf("::::::::::%s\n",ft_strndup(tmp->val, ft_strlen(tmp->val)));		
			free(value);
			return (ft_strndup(tmp->val, ft_strlen(tmp->val)));
		}
		tmp = tmp->next;
	}
	free(value);
	return (ft_strndup("", ft_strlen("")));
}

void	ft_expand(t_token **token, t_env **env)
{
	t_token *tmp_token;
	t_token	*tmp_prev;

	tmp_token = *token;
	while (tmp_token)
	{
		if(tmp_token->type == ENV_VAR || tmp_token->type == SPECIAL_VAR)
		{
			if (tmp_token->prev)
			{
				tmp_prev = get_prev(tmp_token);
				// printf("cccccccccc::::%s and type %d \n",tmp_token->value, tmp_token->type);
				if(tmp_prev->type == HERE_DOC)
				{
					tmp_token->type = CMD;
					tmp_token = tmp_token->next;
					continue;
				}
			}	
			tmp_token->value = ft_remplace_var(tmp_token->value, env);
			tmp_token->type = CMD;
		}
		tmp_token = tmp_token->next;
	}	
}


