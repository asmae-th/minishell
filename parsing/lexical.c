/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:50:07 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 12:30:11 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int ft_check_caracter(char c)
{
	if(c == ' ' || c == '"' || c == '\'' || c == '|'
		|| c == '$'|| c == '<' || c == '>' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char *ft_strndup(char *str, int n)
{
	char *ptr;
	int i;

	i = 0;
	ptr = malloc((n + 1) * sizeof(char *));
	if(!ptr)
		return (NULL);
	while (str[i] && i < n)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft_cmd(char *input, t_token **token, t_token_type type, t_token_state state)
{
	int i;
	
	i = 0;
	while (input[i] && !ft_check_caracter(input[i]))
		i++;
	
	add_token(token, create_token(ft_strndup(input, i),type, state));
	return (input + i);
}

char *ft_space(char *input, t_token **token, t_token_type type, t_token_state state)
{
	add_token(token, create_token(ft_strndup(input, 1), type, state));
	return (input + 1);
}

char *ft_pipe(char *input, t_token **token, t_token_type type, t_token_state state)
{
	add_token(token, create_token(ft_strndup(input, 1), type, state));
	return (input + 1);
}
char *ft_tokenisation(char *input, t_token **token)
{
	if(!ft_check_caracter(*input))
		input = ft_cmd(input ,token, CMD, NORMAL);
	else if(*input == ' ')
		input = ft_space(input,token, A_SPACE, NORMAL);
	else if(*input == '|')
		input = ft_pipe(input,token, PIPE, NORMAL);
	else if(*input == '\'')
		input = ft_single_quote(input, token, CMD, IN_SQUOT);
	else if(*input == '"')
		input = ft_double_quote(input, token, CMD, IN_DQUOT);
	else if(*input == '<')
		input = ft_red_in(input, token, IN_REDIR, NORMAL);
	else if(*input == '>')
	{
		// printf("qqqqqqqqqq errprpr\n");
		input = ft_red_out(input, token, OUT_REDIR, NORMAL);
	}
	else if (*input == '$')
		input = ft_dollar(input, token, ENV_VAR, NORMAL);
	else if(*input == '~')
		ft_home(input, token);
	return (input);
}

t_token *analyse_lexical(char *input, t_env **env)
{
	t_token *token;
	char *clear;
	
	token = NULL;
	clear = input;
	while (input && *input)
	{
		input = ft_tokenisation(input, &token);
		
		// printf("inpit :: %s\n",input);
	}
	ft_expand(&token, env);
	
		// t_token	*tmp = token;
		// 	while (tmp)
		// 	{
		// 			printf("%s\n",tmp->value);
		// 			tmp = tmp->next;
		// 	}
	// t_token	*tmp = token;
			// while (tmp)
			// {
			// 		printf("aaaa::: %d\n",tmp->type);
			// 		tmp = tmp->next;
			// }
	more_analyse(&token);
	free(clear);
	return (token);
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;
// 	char *input;
// 	t_token *token;
// 	t_env	*env;
	
// 	input = NULL;
// 	env = ft_env(env);
// 	while (1)
// 	{
// 	   input = readline("minishell$> ");
// 	   if(!input)
// 			break;
// 		add_history(input);
// 	   token = analyse_lexical(input, &env);
// 	   if(!token)
// 	   {
// 			free(input);
// 	   		printf("ERROR\n");
// 			break;
// 	   }
// 	   t_token	*tmp = token;
// 	   while (tmp)
// 	   {
// 			printf("token : %s and type %d\n",tmp->value, tmp->type);
// 			tmp = tmp->next;
// 	   }
	   
// 		free(input);
// 	   	free(token);
// 	}
// 	clear_history();
// 	return(0);
// }

