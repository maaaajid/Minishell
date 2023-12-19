/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:36:52 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/10 15:36:52 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

# define OP_ERROR "minishell:\
	syntax error near unexpected token `%c%c'\n"
# define HD_ERROR "minishell: warning: here-document delimited end of file \
(`%s')\n"

extern int	g_exit_status;

typedef enum CommandType
{
	COM_ARGUMENT = 1,
	COM_NAME = 2,
	NULL_TOKEN = 0,
	RED_INPUT_SIGNAL = 3,
	RED_INPUT_FILE = 4,
	RED_OUTPUT_SIGNAL = 5,
	RED_OUTPUT_FILE = 6,
	HER_SIGNAL = 7,
	HER_LIMITER = 8,
	APPEND_O_SIGNAL = 9,
	APPEND_O_FILE = 10,
	PIPELINE = 11,
}	t_CommandType;

typedef enum Sigtype
{
	DEF_SEGNAL = 1,
	HER_SEGNAL = 2,
	CHI_SEGNAL = 3,
	PAR_SEGNAL = 4
}	t_sigtype;

typedef struct s_token
{
	char			*value;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_norm
{
	int		i;
	int		start;
	char	quote;
}	t_norm;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_command
{
	char	****command_array;
	char	***command_segments;
	int		**token_types;
	char	**original_commands;
	int		*original_tokens;
	int		*hold_pid;
	int		com_count;
	int		heredoc[15][2];
	int		pipeline[2][2];
	t_env	**env;
}	t_command;

char		*change_unknown_var(char *arg, int *i);
char		***allocate_command_segments(int com_count);
int			count_command_segments(int *original_tokens);
void		norm_helper(char *lin, t_norm *nor, t_token **hea, t_token **tai);
void		last_one(char *lin, t_norm *nor, t_token **head, t_token **tail);
void		false_case(char *lin, t_norm *nor, t_token **head, t_token **tail);
void		norm_main(char *lin, t_norm *nor, t_token **head, t_token **tail);
t_token		*parse_quotes(char *line);
t_token		*breakdown_line(char *line);
t_token		*new_token(char *value, bool is_quoted);
t_env		*ft_list_last(t_env *env);
t_env		*envp_var(char **envp);
t_env		*ft_lst_find(t_env *env, char *found);
t_env		*ft_list_new(char *str);
t_command	*command_ini(char *op_com, t_env *env);
bool		is_whitespace(char c);
bool		check_str(const char *line, const char *str);
bool		is_it_pipeline(const char *line);
bool		isempty_line(char *line);
void		change_value_state(int *state, int c);
char		**splt_commands(char *cmd);
char		*input_parse_op(char *cmd);
bool		check_for_pipe(char c);
int			rl_replace_line(char *str, int n);
bool		check_for_redirection(char c);
bool		check_for_space(char c);
void		ft_listadd_back(t_env **env, t_env *new_env);
int			ft_list_size(t_env *env);
void		my_prompt(t_env *env);
int			ft_arrlen(char **arr);
bool		check_command(int *cmd);
int			*tokenization(char **cmd);
char		*ft_strjoin_many(int num_args, ...);
void		expand_env(char **cmd, int *tokens, t_env *env);
char		*ft_strjoin_char(const char *s1, const char *s2, char c);
void		del_quotes(char **com);
void		ft_free(void **array);
void		ft_list_clear(t_env **env);
void		ft_pwd(t_env *env);
void		ft_echo(char **cmd, int *tok);
int			**split_tokens(int *original_tokens);
int			com_cnt(char **args, int *tokens);
int			check_env_buil(char **cmd_array, int *token_array);
void		launch_env_builtin(char **cmd_arr, int *token, t_command *cmd);
int			check_for_builtin(char **cmd_array, int *token_array);
void		ft_free_command(t_command *command, char *path, char **args);
void		launch_builtin(char **cmd_ar, int *tok, t_command *cmd, int cmd_n);
char		*get_thepath(char **cmd_arg, int *tokens, t_env *env);
char		**split_path(t_env *env);
char		**command_args(char **c_args, int *tokens, t_env *env, char *cmd);
void		close_fd(int fd);
void		execute_commands(char **args, int c, char *path, t_command *cmd);
char		**env_to_array(t_env *env);
void		close_all(int pipe_fd[2][2], int com_cnt);
void		command_initial(char *op_com, t_env **env);
int			handle_redirections(t_command *exec, int cmd_nb);
void		last_command_sts(t_command *command, int i, char *p, char **args);
void		ft_export(char **cmd, t_env **env);
void		ft_unset(char **cmd, t_env **env);
void		ft_env(char **cmd, t_env *env);
void		ft_cd(char **cmd, t_env *env);
int			two_d_len(char **str);
void		op_put(t_env **env, char *str);
void		ft_signals(int state);
int			heredoc(int hd[15][2], char ***commands, int **tokens);
int			chek_herdoc_state(int fd, t_command *command, int cmd_nb);
void		close_prev_hd(int heredoc[15][2], int cmd_nb);
void		close_hd(int hd_arr[15][2]);
void		ft_exit(char **cmd);
void		put_cd_error(t_env *tmp, int flag, char *old);
void		put_big_cd_err(char *old, char *new);
void		export_print(t_env *tmp);
char		*create_new_string(char *ptr, char *arg, int last_end);
t_env		*ft_list_last(t_env *env);
int			status(void);

#endif
