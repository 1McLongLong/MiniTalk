/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:49:38 by touahman          #+#    #+#             */
/*   Updated: 2024/01/10 21:28:09 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*convert_to_binary(char c)
{
	int	ascii_code;
	int	*bits;
	int	i;

	ascii_code = c;
	bits = (int *)malloc(sizeof(int) * 8);
	if (!bits)
		return (0);
	i = 7;
	while (i >= 0)
	{
		// Extract the LSB
		bits[i] = (ascii_code >> i) & 1;
		i--;
	}
	return (bits);
}

void	send_bits(int server_pid, char c)
{
	int	*bits;
	int	i;

	bits = convert_to_binary(c);
	if (!bits)
		exit(1);
	i = 7;
	// Send starting from the MSB
	while (i >= 0)
	{
		if (bits[i] == 1)
			kill(server_pid, SIGUSR1);
		else if (bits[i] == 0)
			kill(server_pid, SIGUSR2);
		usleep(100);
		i--;
	}
	free(bits);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			ft_putstr("Invalid PID!!!\n");
			exit(1);
		}
		str = argv[2];
		while (*str != '\0')
		{
			send_bits(pid, *str);
			str++;
		}
	}
	else
	{
		ft_putstr("You know how to do this, try again!\n");
		exit (1);
	}
	return (0);
}
