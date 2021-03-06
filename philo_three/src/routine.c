/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:50:19 by vgoldman          #+#    #+#             */
/*   Updated: 2020/11/14 16:50:41 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

void	take_forks(t_philo *philo)
{
	sem_wait(g_philosophers.forks);
	sem_wait(philo->mutex);
	msg(philo, FORK);
	if (g_philosophers.stop)
	{
		sem_post(g_philosophers.forks);
		return ;
	}
	sem_wait(g_philosophers.forks);
	if (g_philosophers.stop)
	{
		sem_post(g_philosophers.forks);
		sem_post(g_philosophers.forks);
		return ;
	}
	msg(philo, FORK);
}

void	eat(t_philo *philo)
{
	msg(philo, EAT);
	philo->last_eat = get_timestamp();
	ft_sleep(g_philosophers.time_to_eat);
	++philo->iter;
	sem_post(philo->mutex);
}

void	put_down_forks(void)
{
	sem_post(g_philosophers.forks);
	sem_post(g_philosophers.forks);
}

void	sleep_and_think(t_philo *philo)
{
	msg(philo, SLEEP);
	ft_sleep(g_philosophers.time_to_sleep);
	msg(philo, THINK);
}
