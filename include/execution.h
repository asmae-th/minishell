/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:52:12 by feljourb          #+#    #+#             */
/*   Updated: 2024/12/29 12:44:56 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing.h"
# include <stdio.h>
# include <unistd.h>  // pour chdir
# include <stdlib.h>  // pour getenv
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/libft.h"

// typedef struct s_envp
// {
// 	char			*env; // pour contient str
// 	char			*var; // pour contient -> variable
// 	char			*val; // pour contient -> value
// 	char			*join; // pour contient le +=
// 	struct s_envp	*next;
// }	t_envp;

//________________builtins______________________
int		builtins(t_final_cmd *cmd, t_envp **envp);
int		execute_builtin(t_final_cmd *cmd, t_envp **envp);
void	ft_echo(t_final_cmd *cmd);
void	ft_cd(t_final_cmd *cmd, t_envp **envp);
void	update_env_pwd(t_envp **envp, char *key, char *value);
void	free_pwd_oldpwd(char *oldpwd, char *pwd);
void	ft_pwd(void);
void	ft_exit(t_final_cmd *cmd);
void	ft_envp(t_envp **envp);
void	ft_unset(t_envp **envp, t_final_cmd *cmd);
void	ft_export(t_envp **envp, t_final_cmd *cmd);
void	update_envp_value(t_envp *tmp, t_envp *new_node);
void	free_export(t_envp *newNode);
void	print_export(t_envp *envp);
void	add_or_apdate_envp(t_envp **envp, t_envp *new_node);
void	restaure_redirection(int saved_stdout, int saved_stdin);

//_______________utils_____________________
int		f_isalpha(char *str);
int		f_strcmp(char *s1, char *s2);
int		f_atoi(const char *str);

//___________________execution____________________
void	execute_command_simple(char *path, t_final_cmd *cmd, t_envp **envp);
void	free_arr(char **arr);
char	*find_executable(char *cmd, t_envp **env);
int		execution(t_final_cmd *cmd, t_envp **envp);
int		prepare_and_execute(t_envp **envp, t_final_cmd *cmd);
char	**copie_list_in_array(t_envp **envp);
char	*path_trouve(t_final_cmd *cmd, t_envp **env);
char	*get_path(t_envp **env);
//____________________redirections_&_pipe_____________________
int		apply_redirections(t_final_cmd *redir);
void	close_fds(t_final_cmd *cmd);
// void	pipeline(t_final_cmd *cmd, t_envp **envp);
void	pipeline(t_final_cmd *cmd, t_envp **envp);
void	execute_child(t_final_cmd *cmds, t_envp **envp, int prev_fd, int pipe_fd[2]);
void	close_parent_fds_pipe(int prev_fd, int pipe_fd[2], t_final_cmd *cmds);
void	wait_all_children(void);
void	handle_error(const char *msg, int exit_code);
void	handle_cmd_not_found(const char *cmd);
void	handle_execve_error(char **env);

//__________________basic_list_____________________
void	copie_env_list(t_envp **env, char **envp);
void	free_list(t_envp *list);
void	add_noeud(t_envp **head, t_envp *newNode);
t_envp	*create_noeud(char *str);
void	delete_noeud(t_envp **envp, t_envp *to_delete);
size_t	egale_indice(char *str);
int		plus_egal(char *str);
int		size_list(t_envp **envp);
void	init_struct(t_envp **new_noeud);
void	delete_first_noeud(t_envp **envp, t_envp *to_delete);
void	free_noeud(t_envp *tmp);

#endif