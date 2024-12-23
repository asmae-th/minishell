/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:17:26 by asmae             #+#    #+#             */
/*   Updated: 2024/12/18 09:43:25 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    char *input = ttyname(STDIN_FILENO);

    printf("%s\n",input);

    // while (1)
    // {
    //     input = readline("minishell$>"); // Read input
    //     if (!input) // If input is NULL, exit loop
    //         break;

    //     if (strcmp(input, "hello") == 0) // Break on "hello"
    //     {
    //         free(input); // Free input before breaking
    //         break;
    //     }

    //     add_history(input); // Add input to history
    //     free(input); // Free input after use
    // }

    // rl_clear_history(); // Clear history to free memory

    return 0; // Ensure no memory leaks at exit
}




// void	ft_sup_space(char *str, char ch)
// {
// 	  int i = 0;
//     int j = 0;

//     while (str[i]) {
//         if (str[i] != ch) {
//             str[j++] = str[i];
//         }
//         i++;
//     }
//     str[j] = '\0'; 
// 	// char *str_red;
// 	// int i;
// 	// int j;

// 	// i = 0;
// 	// j = 0;
// 	// str_red = malloc(sizeof);
// 	// while(input[i])
// 	// {
// 	// 	while(input[i] == ' ')
// 	// 		i++;
// 	// 	str_red[j] = input[i];
// 	// 	i++;
// 	// 	j++; 
// 	// }
// 	// return (str_red);
// }


// int	ft_redirection_errors(char *input)
// {
// 	int i;
// 	char *str_red;

// 	str_red = ft_sup_space(input, ' ');
// 	i = 0;
//     while (str_red[i])
// 	{
//         if ((str_red[i] == '>' || str_red[i] == '<')
// 			&& (str_red[i+1] == '\0' || str_red[i+1] == ' '))
//             return (-1);
//         if ((str_red[i] == '>' && str_red[i+1] == '>')
// 			|| (str_red[i] == '<' && str_red[i+1] == '<'))
// 		{
//             if (str_red[i+2] == '\0' || str_red[i+2] == ' ')
//                 return (-1);
//             i++;
//         }
//         if (str_red[i] == '|' && (str_red[i+1] == '>' || str_red[i+1] == '<'))
//             return (-1);
//         i++;
//     }
//     return (1);
// }


