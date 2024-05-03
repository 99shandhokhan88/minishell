/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:10:39 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:40:35 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_exit;

typedef struct s_mini
{
	int		in;
	int		out;
	int		red;
	char	*pwd;
	char	**envv;
}	t_mini;

void	take_action(char **inputs, t_mini *s_hell);
int		get_var_len(char *str);
void	escape(char *src, char *dst, int *i, int *j);
char	*dup_value(char *str);
char	*get_value(char *name, t_mini *s_hell);
void	expander(t_mini *s_hell, char **input_parsed, int *i);
void	len_quote(char **input, int *i, char quote);
int		len_input(char *input);
void	inside_quotes_copy(char **src, char **dst, char quote);
void	input_copy(char *dst, char *src);
char	*format_input(char *input);
int		my_lexer(t_mini *s_hell, char *input);
void	skip_quotes(char *input, int *pos);
int		check_reds(char *str, int *i, char c);
int		my_error(char *input);
void	setup_fds(int newfd[2]);
void	free_inputs(char **inputs);
void	close_reds(t_mini *s_hell);
void	close_fds(int oldfd[2]);
void	exit_pipe(t_mini *s_hell);
int		my_brain(char *parsed_input, t_mini *s_hell, int piped);
void	change_env_pwd(t_mini *s_hell, char **cwd);
void	change_my_pwd(t_mini *s_hell);
int		cd_one(t_mini *s_hell);
int		cd_two(t_mini *s_hell);
int		cd_pwd(char **args, t_mini *s_hell);
void	osema(int cur_fd[2], t_mini *s_hell);
void	my_cd(char **args, t_mini *s_hell);
void	my_echo(char **args);
int		init_envv(char *envv[], t_mini *s_hell);
char	**dup_env(char **envv);
void	my_envv(char **envv);
char	**gen_paths(int index, t_mini *s_hell, char *input);
int		check_exec_path(char **inputs, t_mini *s_hell);
int		check_exec_status(char **inputs, t_mini *s_hell);
int		second_executor(char **inputs, t_mini *s_hell);
int		executor(char **inputs, t_mini *s_hell);
void	my_exec(char **inputs, t_mini *s_hell);
void	my_exit(char **inputs, t_mini *s_hell);
int		len_envv(char **envv);
void	free_envv(char **envv);
int		export_printer(char **envv);
void	export_alone(t_mini *s_hell);
int		envv_index(char *name, t_mini *s_hell);
int		check_export(char *str);
void	replace_envv(char *new_var, t_mini *s_hell, int index);
char	**export_envv(char **old_envv, char *export);
void	my_export(char **inputs, t_mini *s_hell);
void	my_pwd(void);
char	**unset_envv(char **old_env, int index);
void	my_unset(char **inputs, t_mini *s_hell);
int		get_name_len(char *str);
void	red_in(char *str, int i, char **input, t_mini *s_hell);
void	red_append(char *str, int i, char **input, t_mini *s_hell);
void	red_out(char *str, int i, char **input, t_mini *s_hell);
void	extract_command_with_args(char *input);
int		comp_str_ignore_spaces(const char *str1, const char *str2);
int		open_tmp_file_for_writing(void);
void	write_to_tmp_file(int out, const char *line);
int		open_tmp_file_for_reading(void);
void	here_doc(const char *delimiter);
int		pipe_pars(char *input, int pipe_pos, t_mini *s_hell);
int		check_pipe_or_dollar(char **input, int *i, t_mini *s_hell);
int		parser(t_mini *s_hell, char *lexer_input, int pipe);
void	handle_parents(char *input2, t_mini *s_hell, int *fd);
int		my_pipe(char *input1, char *input2, t_mini *s_hell);
char	*get_filename(char *str, int *j);
void	remove_red_input(char **input_address, int i, int j);
void	reds_in_quotes(char *str, int *i, char quote);
void	handle_reds(char **input, int i, t_mini *s_hell);
int		my_redirections(char **parsed_input, t_mini *s_hell);
void	handle_ctrl_c(int sig);
void	setup_signals(void);
void	handle_ctrl_d(t_mini *s_hell, char *input);
char	*next_input(char *str);
size_t	words_count(char *str);
void	copy_new_split(char *src, char *dst, char quote);
char	*create_split(char *src);
char	**split_input(char *str);
void	make_filename(char *src, char *dst, int i, int k);
void	*set_to_zero(void *space, int zero, size_t dimension);
void	*alloc_with_zero(size_t type_count, size_t size);
size_t	len_str(const char *str);
char	*copy_str(char *copy, const char *original);
char	*dup_str(const char *src);
void	s_hell_init(t_mini *s_hell);
size_t	custom_strspn(const char *str, const char *accept);
void	free_shell(t_mini *s_hell);
int		check_pipe_at_beginning(char *input);
int		is_digit(int n);
int		is_alpha(int c);
int		is_alpha_or_digit(int x);
char	*sub_str(char const *str, unsigned int index, size_t len);
size_t	len_my_itoa(int n);
char	*my_itoa(int n);
char	*join_str(char const *s1, char const *s2);
int		comp_str(const char *s1, const char *s2);
char	*str_char(const char *s, int c);
void	print_str_fd(char *str, int fd);
void	print_error(char *str, int status);
char	*str_str(const char *str, const char *to_find);
int		is_number(char *str);
size_t	count_word(const char *s, char c);
char	**my_split(const char *s, char c);
int		my_atoi(const char *str);

#endif
