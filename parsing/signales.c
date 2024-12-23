/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signales.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:46:54 by asmae             #+#    #+#             */
/*   Updated: 2024/12/22 17:00:03 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


int	ft_setter(int code, int mode)
{
	static int	exit_status;

	if (mode)
		exit_status = code;
	return (exit_status);
}

// void signal_handler(int signum)
// {
//     if (signum == SIGINT)
// 	{
//         write(1, "\nminishell$> ", 13);
//     }
// }
void	seg_handler_c(int status)
{
	if (status == SIGINT)
	{
		ft_setter(1, 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ft_signal(void)
{
    // struct sigaction sa;

    // sa.sa_handler = signal_handler;
    // sa.sa_flags = SA_RESTART;
    // sigemptyset(&sa.sa_mask);

    // sigaction(SIGINT, &sa, NULL);
    // signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, seg_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_delet_herdoc(void)
{
	char	*file_name;
	int		i;

	i = 0;

	while (1)
	{
		file_name = ft_strjoin("herdoc ", ft_itoa(i));
		if (!file_name)
			break;
		if (unlink(file_name) == -1)
		{
			free(file_name);
			break;
		}
		free(file_name);
		i++;
	}
}



// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char *input;
// 	t_token *token;
// 	t_final_cmd	*final_cmd;
	
// 	input = NULL;
// 	t_env *new_env;

// 	new_env = ft_env(env);
// 	ft_signal();
// 	while (1)
// 	{
// 		input = readline("minishell$> ");
// 		if(!input)
// 			break;
// 		add_history(input);
// 			token = analyse_lexical(input, &new_env);
// 		if(ft_syntax(token) == OK)
// 		{
// 			final_cmd = ft_organize_cmd(&token,&new_env);	
// 		}
// 		ft_free_token(&token);
// 	}
// 	clear_history();
// 	ft_free_env(&new_env);
// 	return(0);
// }