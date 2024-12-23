/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:07:03 by asmae             #+#    #+#             */
/*   Updated: 2024/12/17 12:05:20 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char *ft_red_in(char *input, t_token **token, t_token_type type, t_token_state state)
{
    int i;

    i = 1;
    while(input[i] && input[i] == '<')
        i++;
    if(i == 2)
        add_token(token, create_token(ft_strndup(input, 2), HERE_DOC, state));
    else if (i == 1)
        add_token(token, create_token(ft_strndup(input, 2), type, state));
    else
    {
        type = SYNTAX_ERROR;
        state = RED_ERR;
        add_token(token, create_token(ft_strdup("RED ERROR"), type, state));
    }
    return (input + i);
}

char *ft_red_out(char *input, t_token **token, t_token_type type, t_token_state state)
{
    int i;

    i = 1;
    while(input[i] && input[i] == '>')
        i++;
    if(i == 2)
        add_token(token, create_token(ft_strndup(input, 2), APPEND, state));
    else if (i == 1)
    {
        
		// printf("qqqqqqqqqq errprpr\n");
        add_token(token, create_token(ft_strndup(input, 2), type, state));
    }
    else
    {
        type = SYNTAX_ERROR;
        state = RED_ERR;
        add_token(token, create_token(ft_strdup("RED ERROR"), type, state));
    }
    return (input + i);
}

char *ft_home(char *input, t_token **token)
{
    // if (input[0] == '~' && (input[1] == '\0' || input[1] == '/'))
    // {
    //     char *home_dir = getenv("HOME"); // Get the user's home directory
        
    //     if (!home_dir)
    //         home_dir = "/"; // Fallback if HOME is not set
    //     add_token(token, create_token(ft_strdup(home_dir), CMD, NORMAL));
    //     return (input + 1); // Move past the '~'
    // }
    // else
        add_token(token, create_token(ft_strndup("$HOME", ft_strlen("$HOME")), ENV_VAR, NORMAL));
        return (input + 1);
}
