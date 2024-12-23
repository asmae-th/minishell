/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_lexical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:31:55 by asmae             #+#    #+#             */
/*   Updated: 2024/11/29 22:49:38 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	ft_handle_quotes(char *input)
{
	int i;
	int	nb_dquotes;
	int	nb_squotes;

	i = 0;
	nb_dquotes = 0;
	nb_squotes = 0;
	while(input[i])
	{
		if(input[i] == '"')
			nb_dquotes++;
		if(input[i] == '\'')
			nb_squotes++;
		i++;
	}
	if(nb_dquotes % 2 != 0)
		return (-1);
	if(nb_squotes % 2 != 0)
		return (-1);
	return (1);
}

void	ft_sup_space(char *str, char ch)
{
	int i = 0;
    int j = 0;

    while (str[i])
	{
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0'; 
}

int	ft_redirection_errors(char *input)
{
	int i = 0;
	ft_sup_space(input, ' ');
    while (input[i])
	{
        if ((input[i] == '>' || input[i] == '<')
			&& (input[i+1] == '\0' || input[i+1] == ' '))
            return (-1);
        if ((input[i] == '>' && input[i+1] == '>')
			|| (input[i] == '<' && input[i+1] == '<'))
		{
            if (input[i+2] == '\0' || input[i+2] == ' ')
                return (-1);
            i++;
        }
        if (input[i] == '|' && (input[i+1] == '>' || input[i+1] == '<'))
            return (-1);
        i++;
    }
    return (1);
}

void	ft_init_token(t_token *token)
{	
	token->state = NORMAL;
	token->type = CMD;
	token->value = NULL;
	token->next = NULL;
}
t_token    *analyse_lexical(char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if(!token)
		return (NULL);
	ft_init_token(token);
	if(ft_handle_quotes(input) == -1)
	{
		token->state = Q_UNCLOSE;
		token->type = SYNTAX_ERROR;
	}
	if(ft_redirection_errors(input) == -1)
	{
		token->state = RED_ERR;
		token->type = SYNTAX_ERROR;
	}
	return (token);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *input;
	t_token *token;
	
	input = NULL;
	while (1)
	{
	   input = readline("minishell$> ");
	   token = analyse_lexical(input);
	   if(!token)
	   	free(input);
	   if(token->type == SYNTAX_ERROR)
	   {
			free(input);
			free(token);
	   		printf("ERROR\n");
			break;
	   }
		free(input);
	   	free(token);
	}
	clear_history();
	return(0);
}
