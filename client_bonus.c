/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:49:03 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/07/31 16:42:57 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	g_signal_received = 0;

static void	handle_ack(int sig)
{
	(void)sig;
	g_signal_received = 1;
}

static void	send_bit(int pid, char bit)
{
	g_signal_received = 0;
	if (bit == '1')
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	while (!g_signal_received)
		pause();
}

static void	send_message(int pid, char *str)
{
	int		i;
	char	c;
	int		counter;

	counter = 0;
	while (*str)
	{
		i = 8;
		c = *str++;
		counter++;
		while (i--)
		{
			if (c & 0x80)
				send_bit(pid, '1');
			else
				send_bit(pid, '0');
			c <<= 1;
		}
	}
	ft_putnbr_fd(counter, 1);
	ft_putchar_fd('\n', 1);
	i = 8;
	while (i--)
		send_bit(pid, '0');
}

void	stop(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr_fd(" Command Line Usage: ./client [PID] [MESSAGE]\n", 2);
		return (1);
	}
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	signal(SIGUSR2, stop);
	send_message(atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
