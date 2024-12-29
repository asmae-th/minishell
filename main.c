/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:37:15 by asmae             #+#    #+#             */
/*   Updated: 2024/12/29 20:00:34 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"
#include "include/execution.h"

void close_file_descriptors(int start_fd)
{
    struct stat fd_stat;
	int	fd;

	while (start_fd < MAX_FD )
	{
		fd = start_fd;
		if(fstat(fd, &fd_stat) == 0)
			close(fd);
		start_fd++;
	}
}
void display_cat_icon()
{

    printf("\033[38;5;213m           WELCOME TO OUR SHELL 😊   \n\033[0m");
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


int minishell(char **env)
{
	char		*input;
	t_token		*token;
	t_final_cmd	*final_cmd;
	t_envp		*new_env;
	
	input = NULL;
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
		token = analyse_lexical(input, &new_env);
		if(ft_syntax(token) == OK)
		{
			final_cmd = ft_organize_cmd(&token,&new_env);
			execution(final_cmd, &new_env);
			ft_delet_herdoc();
			ft_free_final_cmd(&final_cmd);
			close_file_descriptors(3);
			
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
	ft_free_final_cmd(&final_cmd);
	return(0);
}
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	display_cat_icon();
	ft_setter(0, 1);
	minishell(env);
}
