/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 13:43:52 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/10 16:01:40 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

void	run_monitor_helper(void)
{
	int		i;

	g_philosophers.stop = 1;
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		sem_post(g_philosophers.forks);
}
