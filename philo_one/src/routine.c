/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:50:19 by vgoldman          #+#    #+#             */
/*   Updated: 2020/09/26 18:25:30 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&g_philosophers.forks[philo->id]);
	msg(philo, FORK);
	if (g_philosophers.stop)
	{
		pthread_mutex_unlock(&g_philosophers.forks[philo->id]);
		return;
	}
	pthread_mutex_lock(&g_philosophers.forks[(philo->id + 1) %
			g_philosophers.number_of_philosophers]);
	if (g_philosophers.stop)
	{
		pthread_mutex_unlock(&g_philosophers.forks[philo->id]);
		pthread_mutex_unlock(&g_philosophers.forks[(philo->id + 1) %
				g_philosophers.number_of_philosophers]);
		return;
	}
	msg(philo, FORK);
}

void	eat(t_philo *philo)
{
	//pthread_mutex_lock(&philo->mutex);
	msg(philo, EAT);
	usleep(g_philosophers.time_to_eat);
	//pthread_mutex_unlock(&philo->mutex);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_philosophers.forks[philo->id]);
	pthread_mutex_unlock(&g_philosophers.forks[(philo->id + 1) %
			g_philosophers.number_of_philosophers]);
}

void	sleep_and_think(t_philo *philo)
{
	msg(philo, SLEEP);
	usleep(g_philosophers.time_to_sleep);
	msg(philo, THINK);
}
