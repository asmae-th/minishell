/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:16:25 by asmae             #+#    #+#             */
/*   Updated: 2024/12/29 10:41:41 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../libft/libft.h"
# include <asm-generic/signal-defs.h>
# include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define OK 0
# define ERROR 2
# define SYNTAXE_ERR 2
# define MAX_FD	1024

typedef struct s_envp
{
	char			*env; // pour contient str
	char			*var; // pour contient -> variable
	char			*val; // pour contient -> value
	char			*join; // pour contient le +=
	struct s_envp	*next;
}	t_envp;

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
	SLASH,
	SYNTAX_ERROR,
	EXIT_STATUS,
}	t_token_type;

typedef enum e_token_state
{
	NORMAL,
	IN_SQUOT,
	IN_DQUOT,
	Q_UNCLOSE,
	RED_ERR,
}	t_token_state;

typedef enum valid
{
	TRUE,
	FALS,
}	t_herdoc;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_state	state;
	t_herdoc		valid;
	int				index;
	int				node_member;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_position
{
	int	start;
	int	end;
	int	flag;
	int	node_member;
}	t_position;

typedef struct s_env
{
	char			**i_env;
	char			*var;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef enum e_value_type
{
	NONE,
	COMMANDE,
	ARG,
	TFILE,
}	t_value_type;

typedef enum e_file_type
{
	NONEF,
	OUT_FILE,
	IN_FILE,
	APPEND_FILE,
	HEREDOC_FILE,
}	t_file_type;

typedef struct s_cmd
{
	char			*value;
	t_value_type	v_type;
	t_file_type		f_type;
	t_token_type	type;
	t_token_state	state;
	t_herdoc		valid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_tmp_cmd;

typedef struct s_final
{
	char			**arr;
	int				fd_in;
	int				fd_out;
	// char			*file_name;
	struct s_final	*next;
	struct s_final	*prev;
}	t_final_cmd;

typedef struct s_in_out
{
	int		fd_in;
	int		fd_out;
	char	*file_name;
}	t_in_out;

// Environment Management && expand
t_env		*ft_env(char **env);
t_env		*ft_init_env(t_envp**new_env, char **env);
t_env		*creat_env(char *str);
void		add_env(t_envp**new_env, t_envp*new_noud);
int			ft_indice(char *str, char c);
void		ft_free_env(t_envp**env);
void		ft_expand(t_token **token, t_envp**env);
char		*ft_remplace_var(char *value, t_envp**env);
t_token		*get_prev(t_token *token);
int			ft_strcmp(char *s1, char *s2);

// Lexical Analysis
t_token		*create_token(char *val, t_token_type type, t_token_state state);
void		add_token(t_token **token, t_token *new_token);
void		ft_free_token(t_token **token);
t_token		*analyse_lexical(char *input, t_envp**env);
char		*ft_tokenisation(char *input, t_token **token);

// Token Handling
char		*ft_cmd(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_pipe(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_space(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_single_quote(char *input, t_token **token,
				t_token_type t_type, t_token_state s_token);
char		*ft_double_quote(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_dollar(char *input, t_token **token,
				t_token_type t_type, t_token_state s_token);
char		*ft_red_in(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_red_out(char *input, t_token **token,
				t_token_type type, t_token_state state);
char		*ft_home(char *input, t_token **token);
void		more_analyse(t_token **token);
int			handle_other_cases(char **input, int i);
// String and Character Functions
char		*ft_strndup(char *str, int n);
int			ft_check_caracter(char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_remplace_var(char *value, t_envp**env);
char		*supr_quote(char *value, t_token_state state);
int			len_value(char *value, t_token_state state);
int			search_quote(char *value);
char		*assemble_data(t_token *begin, int end);
t_token		*data_assembler(t_token **tokens, t_position *position);
int			affect_index(t_token **token);
void		init_holder(t_position **holder, t_token **tokens);
void		remove_double_quotes(const char *value, char *ptr, int *j);
t_position	*index_getter(t_token **tokens);
void		free_region(t_token **start, t_token **end);

// Syntax Checking
int			ft_syntax(t_token *token);
void		print_error(t_token *token);
int			check_red(t_token *token);
int			check_pipe(t_token *token);
int			redir_case(enum e_token_type type);
t_token		*ft_affter(t_token *token);
t_token		*ft_beffor(t_token *token);
int			is_outred(t_token *behind, t_token *forward);

// Command Organization
t_final_cmd	*ft_organize_cmd(t_token **token, t_envp**env);
void		new_list(t_tmp_cmd **tmp, t_token **token);
void		add_new_cmd(t_tmp_cmd **cmd, t_tmp_cmd *new_cmd);
t_tmp_cmd	*creat_new_cmd(char *value, t_token_type type,
				t_token_state state, t_herdoc valid);
void		ft_free_t_tmp_cmd(t_tmp_cmd **cmd);
void		final_commande(t_final_cmd **f_cmd, t_tmp_cmd **cmd);
t_tmp_cmd	*ft_next(t_tmp_cmd *cmd);
void		add_final_list(t_final_cmd **cmd, t_final_cmd *next_data);
t_final_cmd	*creat_final_cmd(t_tmp_cmd **cmd);
char		**cmd_array(t_tmp_cmd **cmd);
int			arg_count(t_tmp_cmd **cmd);
t_in_out	check_fd(t_tmp_cmd **cmd);
int			fd_open(t_tmp_cmd *cmd);
void		ft_free_final_cmd(t_final_cmd **final);
void		red_file(t_tmp_cmd **cmd);
void		handle_red(t_tmp_cmd **cmd);
void		delete_redir(t_tmp_cmd **cmd);

// Here Document Handling
void		ft_here_doc(t_tmp_cmd **cmd, t_envp**env);
char		*heredoc(char *file, int new_name, t_envp**env, t_herdoc valid);
void		ft_delet_herdoc(void);

// Signal Handling
void		ft_signal(void);
void		signal_handler(int signum);
int			ft_setter(int code, int mode);
void		ft_not_readline(char *readline, int line, char *file);
char		*ft_write(char *readline, int fd_heredoc);
int			ft_check_herdoc_quote(t_tmp_cmd **cmd);
char		*heredoc_expand(char **line, t_envp**env);
char		*get_env_value(char *var_name, t_envp**env);
void		ft_signal_heredoc(void);
void		signal_herdoc_handler(int heredoc);

// Additional Functions
int			ft_check_caracter(char c);
int			true_state(t_token *current);
// Quotes utils
t_token_type	type_is(char c);
int				var_extracter(char *input, int i);
int				set_i(char *input, int i);
int				handle_other_cases(char **input, int i);
void			close_file_descriptors(int start_fd);
#endif