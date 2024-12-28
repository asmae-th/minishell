/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:20:13 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/28 20:24:29 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token_type	type_is(char c)
{
	if (c == '?')
		return (EXIT_STATUS);
	else
		return (SPECIAL_VAR);
}

int	var_extracter(char *input, int i)
{
	while (input[i + 1] && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		i++;
	return (i);
}

int	set_i(char *input, int i)
{
	if (input[i + 1] && input[i + 1] != '\"'
		&& input[i + 1] != '\'')
		i++;
	return (i);
}

int	handle_other_cases(char **input, int i)
{
	if ((*input)[i + 1] == '"' && (*input)[i + 2] == '"')
		i += 2;
	i++;
	return (i);
}
