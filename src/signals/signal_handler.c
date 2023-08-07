#include	"libft.h"
#include	"shell.h"

void	interactive_handler(int sig);
void	non_interactive_handler(int sig);

/* Ctrl-C = SIGINT -> displays a new prompt on a new line. */
/* Ctrl-D = EOF -> exits the shell. */
/* Ctrl-\ = SIGQUIT -> does nothing. */

void	init_signals(int interactive)
{
	struct sigaction	sa;

	/* tcgetattr(STDIN_FILENO, &t); */
	/* t.c_lflag &= ~(ECHOCTL); */
	/* tcsetattr(STDIN_FILENO, TCSAFLUSH, &t); */
	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (interactive)
	{
		sa.sa_handler = &interactive_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = &non_interactive_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		
	}
}

void	interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd_prot("\n", STDOUT_FILENO, 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		(void)sig;
}

void	non_interactive_handler(int sig)
{
	(void)sig;
	ft_putstr_fd_prot("\n", STDOUT_FILENO, 0);
}
