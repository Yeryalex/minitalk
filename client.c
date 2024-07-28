/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:49:03 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/07/28 17:03:54 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	action(int sig)
{
	static int	received;

	received = 0;
	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	send_message(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(500);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(500);
	}
}

int	ft_contain_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr_fd("Command line: ./client <pid> <string>\n", 1);
		return (1);
	}
	if (ft_contain_char(argv[1]) == 1)
	{
		ft_putstr_fd("PID must be only a numeric value\n", 1);
		return (1);
	}
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
