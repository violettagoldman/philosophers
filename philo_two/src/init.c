/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:29:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/10 15:31:35 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern t_philosophers g_philosophers;

static void	init_philo(t_philo *philo, int id)
{
	philo->iter = 0;
	philo->id = id;
	philo->last_eat = get_timestamp();
}

static void	init_helper(void)
{
	if (!(g_philosophers.forks = (t_mutex *)malloc(
					sizeof(t_mutex) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	if (!(g_philosophers.philos = (t_philo *)malloc(
					sizeof(t_philo) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	if (!(g_philosophers.msg = sem_open("MSG", O_CREAT, 0644, 1)))
		err("Semaphore failed");
}

void		init_philosophers(void)
{
	int i;

	g_philosophers.stop = 0;
	g_philosophers.start = get_time();
	init_helper();
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		g_philosophers.philos[i].id_str = ft_itoa(i);
		init_philo(&g_philosophers.philos[i], i);
		if (pthread_mutex_init(&(g_philosophers.forks[i]), NULL))
			err("Mutex failed");
		if (!(g_philosophers.philos[i].mutex = sem_open(
			g_philosophers.philos[i].id_str, O_CREAT, 0644, 1)))
			err("Semaphore failed");
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
		free(g_philosophers.philos[i].id_str);
		pthread_mutex_destroy(&g_philosophers.forks[i]);
		sem_close(g_philosophers.philos[i].mutex);
	}
	sem_close(g_philosophers.msg);
	free(g_philosophers.philos);
	free(g_philosophers.forks);
}
