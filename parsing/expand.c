/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:10:23 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 15:39:08 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_strchr1(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	add_new_tokens(t_token **old_token, char **new_values)
{
	int		i;
	t_token	*new_token;

	i = 0;
	while (new_values[i] != NULL)
	{
		new_token = create_token(new_values[i], NEW_TYPE, NORMAL);
		add_token(old_token, new_token);
		i++;
	}
}

void	remplace_node(t_token **old_token, char **new_values)
{
	t_token	*current;

	current = *old_token;
	while (current)
	{
		if (current->type == ENV_VAR || current->type == SPECIAL_VAR)
		{
			add_new_tokens(old_token, new_values);
			if (current->prev)
				current->prev->next = current->next;
			else
				*old_token = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}

void	handle_split_and_replace(t_token **token, t_token **tmp_token)
{
	char	**ptr;

	if (ft_strchr1((*tmp_token)->value))
	{
		ptr = ft_split((*tmp_token)->value, ' ');
		remplace_node(token, ptr);
		free(ptr);
		*tmp_token = *token;
	}
}

void	ft_expand(t_token **token, t_envp **env)
{
	t_token	*tmp_token;

	tmp_token = *token;
	while (tmp_token)
	{
		if (tmp_token->type == ENV_VAR || tmp_token->type == SPECIAL_VAR)
		{
			if (tmp_token->prev != NULL)
			{
				if (get_prev(tmp_token))
				{
					tmp_token->type = CMD;
					tmp_token = tmp_token->next;
					continue ;
				}
			}
			tmp_token->value = ft_remplace_var(tmp_token->value, env);
			handle_split_and_replace(token, &tmp_token);
			if (tmp_token == *token)
				continue ;
			else
				tmp_token->type = CMD;
		}
		tmp_token = tmp_token->next;
	}
}
