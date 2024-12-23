/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:08:05 by asmae             #+#    #+#             */
/*   Updated: 2024/12/05 09:43:45 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"



// char *ft_strndup(char *str, int n)
// {
//     char *ptr;
//     int i;

//     i = 0;
//     ptr = malloc((n + 1) * sizeof(char *));
//     if(!ptr)
//         return (NULL);
//     while (str[i] && i < n)
//     {
//         ptr[i] = str[i];
//         i++;
//     }
//     ptr[i] = '\0';
//     return (ptr);
// }

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
int main()
{
    char *input;
    // int i = 0;
    input = "asmae";
    // while (input[i] != 'z')
    //     i++;
    // char *s = ft_strndup(input, i);
    printf("%d\n",ft_strcmp(input, "asmae"));
    // free(s);
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;
//     (void)env;

//     char *input = NULL;
//     t_token *token = NULL;

//     while (1) {
//         input = readline("minishell$> ");
//         if (!input)
//             break; // Gestion de CTRL+D
//         add_history(input);

//         token = analyse_lexical(input);

//         if (!token) {
//             printf("ERROR: Memory allocation failed or syntax issue.\n");
//             free(input);
//             break;
//         }

//         // Affiche les tokens
//         t_token *temp = token;
//         while (temp) {
//             printf("Token: %s\n", temp->value);
//             temp = temp->next;
//         }

//         free(input);
//         free_tokens(token);
//     }

//     clear_history();
//     return 0;
// }