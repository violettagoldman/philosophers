/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:15:52 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/16 09:59:06 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

static void	print(t_philo *philo, int type)
{
	char *nb;

	nb = ft_itoa(philo->id + 1);
	write(1, nb, ft_strlen(nb));
	free(nb);
	if (type == FORK)
		write(1, " has taken a fork 🍴", 22);
	else if (type == EAT)
		write(1, " is eating 🍝", 15);
	else if (type == SLEEP)
		write(1, " is sleeping 💤", 17);
	else if (type == THINK)
		write(1, " is thinking 🤔", 17);
	else if (type == DIE)
		write(1, " died 💀", 10);
	write(1, "\n", 1);
}

void		msg(t_philo *philo, int type)
{
	char *nb;

	if (g_philosophers.stop)
		return ;
	pthread_mutex_lock(&g_philosophers.msg);
	if (g_philosophers.stop)
	{
		usleep(10000);
		pthread_mutex_unlock(&g_philosophers.msg);
		return ;
	}
	nb = ft_itoa(get_timestamp());
	write(1, nb, ft_strlen(nb));
	write(1, " ", 1);
	free(nb);
	if (type == OVER)
	{
		write(1, "The dinner is over ✅\n", 23);
		usleep(10000);
		pthread_mutex_unlock(&g_philosophers.msg);
		return ;
	}
	print(philo, type);
	pthread_mutex_unlock(&g_philosophers.msg);
}
