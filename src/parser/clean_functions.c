/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:17:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:17:16 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	free_tokens_and_useless_strings(t_token **token_list)
{
	t_token	*node;
	t_token	*temp;

	if (!token_list)
		return ;
	if (!(*token_list))
		return (free(token_list));
	node = *token_list;
	while (node)
	{
		if (!(node->token_id == WORD || node->token_id == S_QUOTE || \
				node->token_id == D_QUOTE || node->token_id == ENV_VAR))
		{
			free(node->content);
		}
		temp = node->next;
		free(node);
		node = temp;
	}
	free(token_list);
}

void	clean_tokens(t_token **token_list)
{
	t_token	*node;
	t_token	*temp;

	if (!token_list)
		return ;
	if (!(*token_list))
		return (free(token_list));
	node = *token_list;
	while (node)
	{
		temp = node->next;
		free(node->content);
		free(node);
		node = temp;
	}
	free(token_list);
}

void	clean_commands(t_command **command_node)
{
	t_command	*node;
	t_command	*temp;

	if (!command_node || !*command_node)
		return ;
	node = *command_node;
	while (node)
	{
		temp = node->next;
		if (node->args)
			ft_free_split(node->args);
		clean_redirs(node->redir);
		free(node);
		node = temp;
	}
	*command_node = NULL;
}

void	clean_redirs(t_redir *node)
{
	t_redir	*temp;

	if (!node)
		return ;
	while (node)
	{
		if (node->file_name)
			free(node->file_name);
		temp = node->next;
		free(node);
		node = temp;
	}
	free(node);
}
