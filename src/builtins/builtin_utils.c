/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:14:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:14:18 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	ft_putstr_fd_prot(char *s, int fd, int newline)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (write(fd, &s[x], 1) == -1)
			return (-1);
		x++;
	}
	if (newline)
	{
		if (write(fd, "\n", 1) == -1)
			return (-1);
	}
	return (x);
}

int	ft_stris_x(char *s, int (*f)(int))
{
	if (!s || !f)
		return (0);
	while (*s)
	{
		if (f(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

char	*find_path_up(char *path)
{
	int		path_len;
	char	*new_path;

	path_len = ft_strlen(path);
	while (path_len-- > 0)
	{
		if (path[path_len - 1] == '/')
		{
			path_len--;
			break ;
		}
	}
	new_path = ft_substr(path, 0, path_len);
	return (new_path);
}
