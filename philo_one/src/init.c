/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:29:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/09/26 18:18:28 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

static void	init_philo(t_philo *philo, int id)
{
	philo->iter = 0;
	philo->id = id;
	philo->last_eat = 0;
}

void		init_philosophers(void)
{
	int i;

	g_philosophers.stop = 0;
	g_philosophers.start = get_time();
	if (!(g_philosophers.forks = (t_mutex *)malloc(
					sizeof(t_mutex) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	if (!(g_philosophers.philos = (t_philo *)malloc(
					sizeof(t_philo) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	if (pthread_mutex_init(&(g_philosophers.msg), NULL))
		err("Mutex failed");
	if (pthread_mutex_init(&(g_philosophers.die), NULL))
		err("Mutex failed");
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		init_philo(&g_philosophers.philos[i], i);
		if (pthread_mutex_init(&(g_philosophers.forks[i]), NULL))
			err("Mutex failed");
		if (pthread_mutex_init(&(g_philosophers.philos[i].mutex), NULL))
			err("Mutex failed");
	}
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		pthread_create(&(g_philosophers.philos[i].thread), NULL, &run_philo,
				&(g_philosophers.philos[i]));
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		pthread_join(g_philosophers.philos[i].thread, NULL);
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		pthread_mutex_destroy(&g_philosophers.forks[i]);
}

void		free_philosophers(void)
{
	int i;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		pthread_mutex_destroy(&g_philosophers.forks[i]);
		pthread_mutex_destroy(&g_philosophers.philos[i].mutex);
	}
	free(g_philosophers.philos);
	free(g_philosophers.forks);
}