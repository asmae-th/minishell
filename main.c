/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:37:15 by asmae             #+#    #+#             */
/*   Updated: 2025/01/01 21:43:20 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"
#include "include/execution.h"

void	history_acces(char *input)
{
	int		state;
	size_t	i;

	i = 0;
	history(input, i, ft_strlen(input), &state);
	if (state)
		add_history(input);
}

int	minishell_exit_check(char *input, t_envp *new_env)
{
	if (!input)
	{
		ft_setter(EXIT_SUCCESS, 0);
		rl_clear_history();
		free_list(new_env);
		write(1, "exit\n", 5);
		close(STDERR_FILENO);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit(ft_setter(0, 0));
	}
	history_acces(input);
	return (0);
}

int	minishell_loop(t_envp *new_env)
{
	char		*input;
	t_token		*token;
	t_final_cmd	*final_cmd;

	while (1)
	{
		input = readline("\033[1;34m\033[1;32m Minishell$> \033[0m");
		minishell_exit_check(input, new_env);
		token = analyse_lexical(input, &new_env);
		if (ft_syntax(token) == OK)
		{
			final_cmd = ft_organize_cmd(&token, &new_env);
			execution(final_cmd, &new_env);
			ft_delet_herdoc();
			ft_free_final_cmd(&final_cmd);
		}
		else
		{
			ft_setter(2, 1);
			ft_free_token(&token);
			clear_history();
		}
	}
	return (0);
}

int	minishell(char **env)
{
	t_envp	*new_env;

	ft_signal();
	new_env = NULL;
	copie_env_list(&new_env, env);
	minishell_loop(new_env);
	clear_history();
	free_list(new_env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	printf("\033[38;5;213m           WELCOME TO OUR SHELL 😊   \n\033[0m");
	ft_setter(0, 1);
	minishell(env);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
}
