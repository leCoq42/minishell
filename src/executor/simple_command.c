/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:28 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/18 16:42:25 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static void	execute_child_without_pipe(t_shell *shell, t_command *curr);

void	simple_command(t_shell *shell)
{
	int	temp_std_in;
	int	temp_std_out;

	if (check_hd_curr_cmd(shell->command_node) == 1)
		return (set_status(1));
	if (!(shell->command_node->args[0]))
	{
		g_status = handle_redirs_curr_cmd(shell, shell->command_node);
		close_open_fds(shell);
	}
	else if (check_built_in(shell->command_node))
	{
		temp_std_in = dup(STDIN_FILENO);
		temp_std_out = dup(STDOUT_FILENO);
		g_status = handle_redirs_curr_cmd(shell, shell->command_node);
		if (g_status == 0)
			g_status = handle_built_in(shell, shell->command_node);
		close_open_fds(shell);
		redirect_std_in(temp_std_in);
		redirect_std_out(temp_std_out);
	}
	else
		execute_child_without_pipe(shell, shell->command_node);
}

static void	execute_child_without_pipe(t_shell *shell, t_command *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_error_and_set_status("fork fail", 1));
	if (pid == 0)
		execute_non_built_in(shell, curr);
	else
		update_status(pid);
}
