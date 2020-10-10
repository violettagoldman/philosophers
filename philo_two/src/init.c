/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:29:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/10 17:25:04 by vgoldman         ###   ########.fr       */
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
	if (!(g_philosophers.philos = (t_philo *)malloc(
					sizeof(t_philo) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	sem_unlink("/MSG");
	if (!(g_philosophers.msg = sem_open("/MSG", O_CREAT | O_EXCL, S_IRWXU, 1)))
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
		g_philosophers.philos[i].id_str = prefix(ft_itoa(i));
		init_philo(&g_philosophers.philos[i], i);
		sem_unlink(g_philosophers.philos[i].id_str);
		if (!(g_philosophers.philos[i].mutex = sem_open(
			g_philosophers.philos[i].id_str, O_CREAT | O_EXCL, S_IRWXU, 1)))
			err("Semaphore failed");
	}
	sem_unlink("/FORKS");
	if (!(g_philosophers.forks = sem_open("/FORKS", O_CREAT | O_EXCL, S_IRWXU,
		g_philosophers.number_of_philosophers)))
		err("Semaphore failed");
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		pthread_create(&(g_philosophers.philos[i].thread), NULL, &run_philo,
				&(g_philosophers.philos[i]));
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		pthread_join(g_philosophers.philos[i].thread, NULL);
	sem_close(g_philosophers.forks);
}

void		free_philosophers(void)
{
	int i;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		sem_close(g_philosophers.philos[i].mutex);
		sem_unlink(g_philosophers.philos[i].id_str);
		free(g_philosophers.philos[i].id_str);
	}
	sem_close(g_philosophers.forks);
	sem_unlink("/FORKS");
	sem_close(g_philosophers.msg);
	sem_unlink("/MSG");
	free(g_philosophers.philos);
}
