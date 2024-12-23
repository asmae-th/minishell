/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:10:33 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 12:22:34 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char *ft_single_quote(char *input, t_token **token, t_token_type type, t_token_state state)
{
	int i;
	
	i = 1;
	while (input[i] && input[i] != '\'')
		i++;
	if(input[i] !=  '\'')
	{
		type = SYNTAX_ERROR;
		state = Q_UNCLOSE;
		add_token(token, create_token(ft_strdup("ERROR"), type, state));
	}
	else
	{
		add_token(token, create_token(ft_strndup(input + 1, i - 1), type, state));
		i++;
	}       
	return (input + i);
}

// char *ft_double_quote(char *input, t_token **token, t_token_type type, t_token_state state)
// {
//     int i;

// 	i = 0;
//     while (input[i] && input[i] != '"')
//     {
//         if (input[i] == '$')
//         {
//             if (i > 1) // Aiout du contenu avant le $
//             {
//                 add_token(token, create_token(ft_strndup(input + 1, i - 1), type, state));
//                 input = input + i; // Avancer après le contenu
//                 i = 0;
//             }
//             input = ft_dollar(input, token);
//         }
//         else
// 			i++;
//     }
//     if (input[i] != '"')
//     {
//         add_token(token, create_token(ft_strdup("SYNTAX_ERROR"), SYNTAX_ERROR, Q_UNCLOSE));
//         return (input + i);
//     }
//     if (i > 1)
//     {
//                 printf("sete : %d\n",state);
//         // printf("helloo111111\n");
//         add_token(token, create_token(ft_strndup(input + 1, i - 1), type, state));
//     }
//     // else
//     //     printf("hello1\n");
//     return (input + i + 1);
// }


// char *ft_dollar(char *input, t_token **token)
// {
//     int i;

// 	i = 1;
//     if (input[i] && input[i] == '?')
//     {
//         add_token(token, create_token(ft_strdup("$?"), EXIT_STATUS, NORMAL));
//         return (input + 2); // $?
//     }
//     else if(input[i] && (ft_isdigit(input[i]) || input[i] == '$'))
//     {
//         add_token(token, create_token(ft_strdup("$?"), SPECIAL_VAR, NORMAL));
//         return (input + 2);
//     }
//     while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
//         i++;
//     if (i == 1)
//     {
//         add_token(token, create_token(ft_strdup("$"), ENV_VAR, NORMAL));
//         return (input + 1);
//     }
//     char *var_name = ft_strndup(input + 1, i - 1);
//     add_token(token, create_token(var_name, ENV_VAR, NORMAL));
//     return (input + i);
// }


int content_quote(char **input, t_token **token, t_token_type type, t_token_state state)
{
    int i;

    i = 0;
    while ((*input)[i] && (*input)[i] != '"')
    {
        if ((*input)[i] == '$')
        {
            if (i) // Aiout du contenu avant le $
            {
                add_token(token, create_token(ft_strndup((*input), i), type, state));
            }
            (*input) = ft_dollar((*input) + i, token,ENV_VAR, state); // Avancer après le contenu
            i = 0;
            // input = ft_dollar(input, token);
        }
        else
        {
            if((*input)[i + 1] == '"' && (*input)[i + 2] == '"')
                i += 2;
			i++;
        }
    }
    return (i);
}




char *ft_double_quote(char *input, t_token **token, t_token_type type, t_token_state state)
{
    int i;

    input++;
	i = content_quote(&input, token, type, state);
    if(input[i] == 0 || !(*input))
    {
        type = SYNTAX_ERROR;
        state = Q_UNCLOSE;
        if(*input == input[i])
        {
            add_token(token, create_token(ft_strndup("SYNATAXE_ERROR", ft_strlen("SYNATAXE_ERROR")),type, state));
            return (input + i);
        }
    }
    add_token(token, create_token(ft_strndup(input, i),type, state));
    if(input[i] == '"')
        i++;
    
    return (input + i);
}






// char *ft_dollar(char *input, t_token **token)
// {
// 	int i;
// 	char *var_name;

// 	i = 1;
// 	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
// 		i++;
// 	if(i == 1)
// 	{
// 		add_token(token, create_token(ft_strdup("$"), ENV_VAR, NORMAL));
// 		return(input + i);
// 	}
// 	else
// 	{
// 		var_name = ft_strndup(input + 1, i - 1);
// 		add_token(token, create_token(var_name, ENV_VAR, NORMAL));
// 		return(input + i);
// 	}

// }



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

char	*ft_dollar(char *input, t_token **token, t_token_type t_type, t_token_state s_token)
{
	int	i;

	i = 0;
	if (*(input + 1) && (ft_isdigit(*(input + 1)) || *(input + 1) == '?' || *(input + 1) == '$'))
	{
    // printf("hello quote\n");
		t_type = type_is(*(input + 1));
		add_token(token, create_token(ft_strndup(input, 2),
				t_type, s_token));
		return (input + 2);
	}
	i = var_extracter(input, i);
	if (!i)
		t_type = CMD;
	if (i)
		add_token(token, create_token(ft_strndup(input, i + 1), t_type, s_token));
	else
	{
		i = set_i(input, i);
		add_token(token, create_token(ft_strndup(input, i + 1), t_type, s_token));
	}
	return (input + i + 1);
}

