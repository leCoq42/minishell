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

# define TOKEN_DELIMITERS "|'\"$<> "
# define NORMAL_DELIMITERS "|'\"$ "
# define SPECIAL_DELIMITERS "<>" 

# define SUCCESS 0 
# define ERROR 1

typedef	struct s_token
{
	char	*content;
	int		token_id;
	struct s_token	*next;
}				t_token;

enum token_id
{
	PIPE,
	GREAT,
	LESS,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR,
	WHITE_SPACE
};

// 					TOKENIZER.C
t_token	**		tokenize(const char *s);
// 					TOKEN_LIST_FUNCTIONS.C
 void		add_token(t_token **token_list, t_token *token);
 t_token	*ft_new_token(void *content);
 void	print_tokens(t_token *token);
 void analyze_greater_lesser(t_token *token);
 int analyze_quotations(t_token *token);

#endif