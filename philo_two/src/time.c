/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:00:16 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/15 18:48:17 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

int			get_timestamp(void)
{
	return ((int)(get_time() - g_philosophers.start));
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void		ft_sleep(int ms)
{
	uint64_t now;

	now = get_time();
	while (get_time() - now < (uint64_t)ms)
		usleep(DELAY_SLEEP);
}
