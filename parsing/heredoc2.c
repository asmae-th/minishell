/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:17:12 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/28 20:34:07 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	signal_herdoc_handler(int heredoc)
{
	if (heredoc == SIGINT)
	{
		ft_setter(1, 1);
		if (dup2(STDERR_FILENO, 0) == -1)
		{
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

char	*get_env_value(char *var_name, t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->var, var_name) == 0)
			return (ft_strdup(current->val));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*process_env_variable(char **tmp, t_envp **env, char *result)
{
	char	*var_name;
	char	*var_value;
	int		j;

	// Extraire la portion avant la variable et l'ajouter au résultat
	result = ft_strjoin(result, ft_substr(*tmp, 0, 0));
	(*tmp)++; // Passer le caractère '$'
	// Identifier le nom de la variable
	j = 0;
	while ((*tmp)[j] && (ft_isalnum((*tmp)[j]) || (*tmp)[j] == '_'))
		j++;
	// Récupérer la variable d'environnement et sa valeur
	var_name = ft_substr(*tmp, 0, j);
	*tmp += j; // Avancer le pointeur au-delà de la variable
	// Récupérer la valeur de l'environnement et mettre à jour le résultat
	var_value = get_env_value(var_name, env);
	free(var_name);
	result = ft_strjoin(result, var_value);
	free(var_value);
	return (result);
}

char	*process_plain_text(char **tmp, char *result)
{
	int		i;
	char	*start;

	i = 0;
	start = *tmp;
	// Parcourir la chaîne jusqu'à rencontrer un '$' ou la fin
	while ((*tmp)[i] && (*tmp)[i] != '$')
		i++;
	// Ajouter la portion de texte sans '$' au résultat
	result = ft_strjoin(result, ft_substr(start, 0, i));
	// Avancer le pointeur
	*tmp += i;
	return (result);
}

char	*heredoc_expand(char **line, t_envp **env)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(""); // Initialiser le résultat comme une chaîne vide
	tmp = *line;
	while (tmp && *tmp)
	{
		if (*tmp == '$')
		{
			result = process_env_variable(&tmp, env, result);
		}
		else
		{
			result = process_plain_text(&tmp, result);
		}
	}
	free(*line);
	*line = result;
	return (result);
}
