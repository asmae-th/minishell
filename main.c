/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:37:15 by asmae             #+#    #+#             */
/*   Updated: 2024/12/28 15:32:25 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"
#include "include/execution.h" //u zedt hada bach tkhedmi b execution 




#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[91m"
#define MAGENTA "\033[35m"
#define CYAN "\033[38;5;213m"
#define RESET "\033[0m"

void display_cat_icon()
{

    printf(CYAN "           WELCOME TO OUR SHELL 😊   \n" RESET);
}

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
	t_envp *new_env;
	display_cat_icon();
	ft_setter(0, 1);
	new_env = NULL;
	copie_env_list(&new_env, env);
	ft_signal();
	while (1)
	{
		input = readline("\033[1;34m😎\033[1;32m Minishell$> \033[0m");
		if(!input)
		{
			ft_setter(EXIT_SUCCESS, 1);
			rl_clear_history();
			free_list(new_env);
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(input);
			// printf("hi\n");
		token = analyse_lexical(input, &new_env);
		
		// printf("valuuuuuuuuu ::: %s\n",token->value);
		
		if(ft_syntax(token) == OK)
		{
			
			
			final_cmd = ft_organize_cmd(&token,&new_env);
			// print_string(final_cmd->arr);
			// ft_free_final_cmd(&final_cmd);
			// (void)final_cmd;
			// printf("file name = %s\n",final_cmd->file_name);
			execution(final_cmd, &new_env); //rani zedt lik gha had star
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
	free_list(new_env);
	return(0);
}
