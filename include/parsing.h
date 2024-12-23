/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:16:25 by asmae             #+#    #+#             */
/*   Updated: 2024/12/23 14:57:43 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include"../libft/libft.h"
#include <asm-generic/signal-defs.h>
#include <errno.h>

#define OK 0
#define	ERROR 2
#define SYNTAXE_ERR 2

typedef enum e_token_type
{
	CMD,
	A_SPACE,
	PIPE,
	OUT_REDIR,
	IN_REDIR,
	ENV_VAR,
	SPECIAL_VAR,
	HERE_DOC,
	APPEND,
	SYNTAX_ERROR,
	EXIT_STATUS,
} t_token_type;

typedef enum	e_token_state
{
	NORMAL,
	IN_SQUOT,
	IN_DQUOT,
	Q_UNCLOSE,
	RED_ERR,
}t_token_state;

typedef	enum valid
{
	TRUE,
	FALS,
}t_herdoc;

typedef struct s_token
{
	char        *value;      // Valeur du token
	t_token_type type;       // Type du token (commande, argument, pipe, etc.)
	t_token_state state;
	t_herdoc	valid;
	int			index;
	int					node_member;
	struct s_token *next;    // Pointeur vers le prochain noud
	struct s_token	*prev;
} t_token;

typedef struct s_position
{
	int	start;
	int end;
	int flag;
	int node_member;
}t_position;

typedef struct s_env
{
	char **i_env;
	char *var;
	char *val;
	struct s_env *next;
	struct s_env *prev;
} t_env;

typedef enum e_value_type
{
	NONE,
	COMMANDE,
	ARG,
	TFILE,
}value_type;



typedef	enum e_file_type
{
	NONEF,
	OUT_FILE,
	IN_FILE,
	APPEND_FILE,
	HEREDOC_FILE,
}file_type;

typedef struct s_cmd
{
	char			*value;
	value_type		v_type;
	file_type		f_type;
	t_token_type	type;
	t_token_state	state;
	t_herdoc		valid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}tmp_cmd;

typedef struct s_final
{
	char	**arr;
	int		fd_in;
	int		fd_out;
	struct s_final *next;
	struct s_final	*prev;
}t_final_cmd;

typedef struct s_in_out
{
	int		fd_in;
	int		fd_out;
}t_in_out;


t_env	*ft_env(char	**env);
t_env	*ft_init_env(t_env **new_env,char **env);
t_env	*creat_env(char *str);
void	add_env(t_env **new_env, t_env *new_noud);
int		ft_indice(char *str, char c);
void	ft_free_env(t_env **env);

t_token *analyse_lexical(char *input, t_env **env);
char	*ft_tokenisation(char *input, t_token **token);
char	*ft_pipe(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_space(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_cmd(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_strndup(char *str, int n);
int		ft_check_caracter(char c);
t_token	*create_token(char *val, t_token_type type, t_token_state state);
void	add_token(t_token **token, t_token *new_token);
void	ft_free_token(t_token **token);
void    more_analyse(t_token **token);
void tokens_cleaner(t_token **tokens);
char    *supr_quote(char *value, t_token_state state);
int len_value(char *value, t_token_state state);
int search_quote(char *value);


void specialcase_handler(t_token **tokens);


char	*ft_single_quote(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_double_quote(char *input, t_token **token, t_token_type type, t_token_state state);
// char	*ft_dollar(char *input, t_token **token);
char	*ft_dollar(char *input, t_token **token, t_token_type t_type, t_token_state s_token);

char	*ft_red_in(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_red_out(char *input, t_token **token, t_token_type type, t_token_state state);
char	*ft_home(char *input, t_token **token);

void	ft_expand(t_token **token, t_env **env);
int		ft_strcmp(char *s1, char *s2);
char *ft_remplace_var(char *value, t_env **env);

int		ft_syntax(t_token *token);
void	print_error(t_token *token);
int		check_red(t_token *token);
int		check_pipe(t_token *token);
int		redir_case(enum e_token_type type);
t_token *ft_affter(t_token *token);
t_token *ft_beffor(t_token *token);
int		is_outred(t_token *behind, t_token *forward);

t_final_cmd *ft_organize_cmd(t_token **token, t_env **env);
void    new_list(tmp_cmd **tmp, t_token **token);
void	add_new_cmd(tmp_cmd **cmd, tmp_cmd *new_cmd);
// tmp_cmd	*creat_new_cmd(char *value, t_token_type type, t_token_state state);
tmp_cmd	*creat_new_cmd(char *value, t_token_type type, t_token_state state, t_herdoc valid);

void ft_free_tmp_cmd(tmp_cmd **cmd);

void    final_commande(t_final_cmd **f_cmd, tmp_cmd **cmd);
tmp_cmd *ft_next(tmp_cmd *cmd);
void    add_final_list(t_final_cmd **cmd, t_final_cmd *next_data);
t_final_cmd *creat_final_cmd(tmp_cmd **cmd);
char **cmd_array(tmp_cmd **cmd);
int arg_count(tmp_cmd **cmd);
t_in_out check_fd(tmp_cmd **cmd);
int	fd_open(tmp_cmd *cmd);
void	ft_free_final_cmd(t_final_cmd **final);

void    ft_here_doc(tmp_cmd **cmd, t_env **env);
// char *heredoc(char *file,int new_name, t_token_state state, t_env **env);
// char *heredoc(char *file,int new_name, t_token_state state, t_env **env, tmp_cmd **cmd);
char *heredoc(char *file,int new_name, t_token_state state, t_env **env, t_herdoc valid);
// char *heredoc(char *file,int new_name, t_token_state state, t_env **env, t_token_state state1);
void	ft_delet_herdoc(void);

void ft_signal(void);
void signal_handler(int signum);
int	ft_setter(int code, int mode);
#endif