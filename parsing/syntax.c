/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:11:50 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 12:22:09 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	print_error(t_token *token)
{
	if(token->state == Q_UNCLOSE)
		write(1,"quotes (\' or \") unclose \n", 25);//use write
	else if(token->state == RED_ERR)
		printf("redirections error\n");//use write
	// else
	// 	printf("rad lbal rah kyn error\n");//use write
	write(1, "\n", 1);

}

int	check_red(t_token *token)
{
	t_token	*tokens;

	if (token->next)
		if (token->type == OUT_REDIR && token->next->type == PIPE)
		{
			// printf("heloolool\n");
			return (OK);
		}
	tokens = token->next;
	while (tokens && tokens->type == A_SPACE)
		tokens = tokens->next;
	if (!tokens || (tokens->type != CMD && tokens->type != EXIT_STATUS)
		|| (!ft_strcmp(tokens->value, "") && tokens->state == NORMAL))
		{
			return (ERROR);
		}
	return (OK);
}

t_token *ft_beffor(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp && tmp->type == A_SPACE)
		tmp = tmp->prev;
	return (tmp);
}

t_token *ft_affter(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp && tmp->type == A_SPACE)
		tmp = tmp->next;
	return (tmp);
}

int	redir_case(enum e_token_type type)
{
	if(type == IN_REDIR || type == OUT_REDIR || type == APPEND
		|| type == HERE_DOC)
		return (1);
	else
		return (0);
}
int	is_outred(t_token *behind, t_token *forward)
{
	if (behind->type == OUT_REDIR)
	{
		if (behind->next->type == PIPE && !redir_case(forward->type))
		{
			return (1);
		}
		else
		{
			
			return (0);
		}
	}
	return (0);
}

int	check_pipe(t_token *token)
{
	t_token	*beffor;
	t_token	*affter;
	
	beffor = ft_beffor(token);
	affter = ft_affter(token);
	if (!beffor || !affter
	|| (beffor->type != CMD && beffor->type != EXIT_STATUS && is_outred(beffor, affter))// !
	|| (affter->type != CMD && affter->type != EXIT_STATUS && !redir_case(affter->type)))
	{
		printf("hna kyn errprprr\n");
		return (ERROR);
	}
	return (OK);
}
int ft_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SYNTAX_ERROR)
		{	
			print_error(tmp);
			return(ERROR);
		}
		if(tmp->type == OUT_REDIR || tmp->type == IN_REDIR || tmp->type == APPEND || tmp->type == HERE_DOC)
		{
			// printf("qqqqqqqqqq errprpr\n");
			if(check_red(tmp) == ERROR)
				return(print_error(tmp), ERROR);
		}
		if(tmp->type == PIPE)
		{
			if(check_pipe(tmp) == ERROR)
			{
				// printf("helooooo\n");
				return(print_error(tmp), ERROR);
			}
		}
		tmp = tmp->next;
	}
	return(OK);
}