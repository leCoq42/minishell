#include "shell.h"
#include "libft.h"

t_token	**tokenize(char *s)
{
	size_t	start;
	size_t	end;
	char	*token_string;
	t_token	*token;
	t_token	**token_list;
    char	*trimmed;

    trimmed = ft_strtrim(s, " ");
    if (!trimmed)
 		return (NULL);
	token_list = ft_calloc(1, sizeof(t_token *));
	if (!token_list)
		return (free(trimmed),NULL);
	start = 0;
	while (trimmed[start])
	{
		end = find_next_token(trimmed, start);
		/* printf("start: %zu\nend: %zu\n", start, end); */
		if (start == end)
			break ;
		token_string = ft_substr(trimmed, start, end - start);
		if (!token_string)
			return (free(trimmed), clean_tokens(token_list), NULL);
		token = ft_new_token(token_string);
		if (!token)
			return (free(trimmed), clean_tokens(token_list), NULL);
		add_token_back(token_list, token);
		start = end;
		while(trimmed[start] && trimmed[start] == ' ')
			start++;
		/* if (end - 1 > start && trimmed[end - 1] == ' ') */
		/* 	start = end - 1; */
	}
	if (start == 0)
		return (free(trimmed), free(token_list), NULL);
	*token_list = remove_white_space(*token_list);
	return (free(trimmed), token_list); // trimmed is mallocced in ft_strtrim
}

size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;

	if (!s[start])
		return (start);
	end = start + 1;
	if (ft_strchr(SPECIAL_DELIMITERS, s[start]) && s[start + 1] && s[start] == s[start + 1])
		return (start + 2);
	else if (s[start] == '\\') // <- segfault
	{
		if (s[end])
			return (end + 1);
		return (end);
	}
	else if (ft_strchr("\"\'", s[start])) // <- segfault, hier nog goed naar kijken
    {
		while (s[end])
		{
			if (s[end] == s[start] && s[end - 1] != '\\')  // <- echo "\"\"" klopt niet
				break ;
			end++;
		}
        if (s[end])
			return (end + 1);
        else
            return (end);
	}
	else if (s[start] == '$') // hier nog ff goed naar kijken
	{
		while(s[end] && !(ft_strchr(TOKEN_DELIMITERS, s[end])))
			end++;
		return (end);
	}
	else if (ft_strchr(TOKEN_DELIMITERS, s[start]))
		return (start + 1);
	while (s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
			return (end);
        end++;
	}
	return (end);
}

void	print_tokens(t_token *top)
{
	int			size;
	const int	con = list_token_size(top);
	const char	*token_name[11] = {
	[0] = "TOKEN",
	[1] = "PIPE",
	[2] = "GREAT",
	[3] = "APPEND",
	[4] = "LESS",
	[5] = "HEREDOC",
	[6] = "S_QUOTE",
	[7] = "D_QUOTE",
	[8] = "ENV_VAR",
	[9] = "WHITE_SPACE",
	[10] = "WORD"
	};

	size = list_token_size(top);
	printf("\n\t-=-  TOKEN PRINT [%d] -=-\n", con);
	while (size--)
	{
		printf("TOKEN [%02d]\tid: %s [%d]\tstr: {%s}\n\n", (con - size), token_name[top->token_id], top->token_id, top->content);
		top = top->next;
	}
	return ;
}

