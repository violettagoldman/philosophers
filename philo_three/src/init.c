/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:29:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/11/05 19:10:55 by vgoldman         ###   ########.fr       */
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
	int i;

	if (!(g_philosophers.philos = (t_philo *)malloc(
					sizeof(t_philo) * g_philosophers.number_of_philosophers)))
		err("Malloc error");
	sem_unlink("/MSG");
	if (!(g_philosophers.msg = sem_open("/MSG", O_CREAT | O_EXCL, S_IRWXU, 1)))
		err("Semaphore failed");
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
}

void		init_philosophers(void)
{
	int i;

	g_philosophers.stop = 0;
	g_philosophers.start = get_time();
	init_helper();
	sem_unlink("/FORKS");
	if (!(g_philosophers.forks = sem_open("/FORKS", O_CREAT | O_EXCL, S_IRWXU,
		g_philosophers.number_of_philosophers)))
		err("Semaphore failed");
	i = -1;
	run_threads();
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
	g_philosophers.forks = NULL;
	sem_close(g_philosophers.msg);
	sem_unlink("/MSG");
	free(g_philosophers.philos);
}

void		*run_meal_counter(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!g_philosophers.stop)
	{
		sem_wait(philo->mutex);
		if (g_philosophers.limit && check_meal())
		{
			msg(philo, OVER);
			run_monitor_helper();
		}
		sem_post(philo->mutex);
		usleep(DELAY_MONITOR);
	}
	return (NULL);
}
