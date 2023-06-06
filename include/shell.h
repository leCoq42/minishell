#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <stdbool.h>
# include <readline/readline.h>

# define TOKEN_DELIMITERS "|><\'\"$\\ "
# define TOKEN_DELIMITER_SET "-|>A<H\'\"$ W"
# define SPECIAL_DELIMITERS "<>"

# define SUCCESS 0
# define ERROR 1

typedef	struct s_token
{
	char			*content;
	int				token_id;
	struct s_token	*next;
}	t_token;

typedef struct s_env_list
{
    char                *name;
    char                *content;
    struct s_env_list   *next;
}   t_env_list;

typedef struct s_shell
{
	t_env_list	*env;



} t_shell;

enum token_id
{
	TOKEN,
	PIPE,
	GREAT,
	APPEND,
	LESS,
	HEREDOC,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR,
	WHITE_SPACE,
	WORD
};

//			TOKENIZER.C
t_token	**		tokenize(char *s);
size_t			find_next_token(const char *s, size_t end);
void			print_tokens(t_token *top);
// 			TOKEN_LIST_FUNCTIONS.C
void			add_token(t_token **token_list, t_token *token);
t_token			*ft_new_token(char *content);
int				get_token_id(char *content);
size_t			list_token_size(t_token *t_list);
//			ANALYZE_TOKENS.C
int				analyze_tokens(t_token *top);
int				check_tokens(int id_1, int id_2);
//			Builtins
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(t_command *cmd, t_shell *shell);
int				ft_putstr_fd_protected(char *s, int fd, int newline);

#endif