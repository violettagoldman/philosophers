/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:02 by vgoldman          #+#    #+#             */
/*   Updated: 2020/11/14 16:50:13 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophers g_philosophers;

int			check_meal(void)
{
	int i;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		if (g_philosophers.philos[i].iter <
		g_philosophers.number_of_time_each_philosopher_must_eat)
			return (0);
	return (1);
}

void		*run_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!g_philosophers.stop && (!g_philosophers.limit ||
		philo->iter < g_philosophers.number_of_time_each_philosopher_must_eat))
	{
		sem_wait(philo->mutex);
		if (!g_philosophers.stop && get_timestamp() - philo->last_eat >
			g_philosophers.time_to_die && (!g_philosophers.limit || philo->iter
			< g_philosophers.number_of_time_each_philosopher_must_eat))
		{
			msg(philo, DIE);
			run_monitor_helper();
		}
		sem_post(philo->mutex);
		ft_sleep(DELAY_MONITOR);
	}
	return (NULL);
}

void		*run_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo*)arg;
	pthread_create(&monitor, NULL, &run_monitor, philo);
	pthread_detach(monitor);
	usleep(philo->id * DELAY_START);
	while (!g_philosophers.stop && (!g_philosophers.limit ||
		philo->iter < g_philosophers.number_of_time_each_philosopher_must_eat))
	{
		if (!g_philosophers.stop)
			take_forks(philo);
		if (!g_philosophers.stop)
			eat(philo);
		if (!g_philosophers.stop)
			put_down_forks();
		if (!g_philosophers.stop)
			sleep_and_think(philo);
	}
	return (NULL);
}

void		run_threads(void)
{
	int			i;
	int			pid;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			run_philo(&g_philosophers.philos[i]);
			exit(0);
		}
		else
			g_philosophers.philos[i].pid = pid;
	}
	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
		waitpid(g_philosophers.philos[i].pid, NULL, 0);
}

int			main(int argc, char **argv)
{
	parse_args(argc, argv);
	init_philosophers();
	free_philosophers();
	return (0);
}
