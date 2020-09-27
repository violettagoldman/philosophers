/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:37:56 by vgoldman          #+#    #+#             */
/*   Updated: 2020/09/27 17:31:57 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

void		err(const char *msg)
{
	int i;

	i = 0;
	while (msg[i])
		i++;
	write(1, msg, i);
	write(1, "\n", 1);
	exit(1);
}

static void	check_args(void)
{
	if (g_philosophers.number_of_philosophers <= 0)
		err("Invalid number of philosophers.");
	if (g_philosophers.time_to_die < 0)
		err("Invalid time to die.");
	if (g_philosophers.time_to_eat < 0)
		err("Invalid time to eat.");
	if (g_philosophers.limit &&
			g_philosophers.number_of_time_each_philosopher_must_eat < 0)
		err("Invalid number of time each philosopher must eat.");
}

void		parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		err("Wrong number of arguments.");
	g_philosophers.number_of_philosophers = ft_atoi(argv[1]);
	g_philosophers.time_to_die = ft_atoi(argv[2]);
	g_philosophers.time_to_eat = ft_atoi(argv[3]) * 1000;
	g_philosophers.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		g_philosophers.number_of_time_each_philosopher_must_eat =
			ft_atoi(argv[5]) * 1000;
		g_philosophers.limit = 1;
	}
	else
		g_philosophers.limit = 0;
	check_args();
}
