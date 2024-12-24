/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:37:15 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 17:31:25 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/execution.h" //u zedt hada bach tkhedmi b execution 


void print_string(char **str)
{
    int i = 0;

    if (str == NULL)
    {
        printf("Le tableau de chaînes est NULL.\n");
        return;
    }

    while (str[i] != NULL)
    {
        printf("%s\n", str[i]);
        i++;
    }
}


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	t_token *token;
	t_final_cmd	*final_cmd;
	
	input = NULL;
	t_env *new_env;

	ft_setter(0, 1);
	new_env = ft_env(env);
	ft_signal();
	while (1)
	{
		input = readline("minishell$> ");
		if(!input)
		{
			ft_setter(EXIT_SUCCESS, 1);
			rl_clear_history();
			ft_free_env(&new_env);
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(input);
		token = analyse_lexical(input, &new_env);
		
		// printf("valuuuuuuuuu ::: %s\n",token->value);
		
		if(ft_syntax(token) == OK)
		{
			
			
			final_cmd = ft_organize_cmd(&token,&new_env);
			// print_string(final_cmd->arr);
			// ft_free_final_cmd(&final_cmd);
			// (void)final_cmd;
			execution(final_cmd, env); //rani zedt lik gha had star
			// printf("ccccccc\n");
			ft_delet_herdoc();
			// t_token	*tmp = token;
			// while (tmp)
			// {
			// 		printf("%d\n",tmp->state);
			// 		tmp = tmp->next;
			// }
		}
		else
		{
			ft_setter(SYNTAX_ERROR,1);
			ft_free_token(&token);
		}
	}
	clear_history();
	ft_free_token(&token);
	ft_free_env(&new_env);
	return(0);
}
