/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:55:33 by touahman          #+#    #+#             */
/*   Updated: 2024/01/10 16:24:01 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static int	bit = 0;
	static char	c = 0;

	(void)context;
	if (pid != info->si_pid)
	{
		bit = 0;
		c = 0;
		pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		c = (c << 1) + 1;
	else
		c <<= 1;
	if (bit == 7)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	else
		bit++;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	(void)argv;
	if (argc != 1)
		ft_putstr("ONLY './server' AS INPUT\n");
	else
	{
		pid = getpid();
		ft_putstr("PID: ");
		ft_putnbr(pid);
		ft_putstr("\nMESSAGE INCOMING:\n");
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &handler;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		while (1)
			pause();
	}
	return (0);
}
