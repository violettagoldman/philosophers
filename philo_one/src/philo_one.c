/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:02 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/10 14:23:48 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophers g_philosophers;

int			check_meal(void)
{
	int i;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		if (g_philosophers.philos[i].iter <
		g_philosophers.number_of_time_each_philosopher_must_eat)
			return (0);
	}
	return (1);
}

void		*run_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!g_philosophers.stop)
	{
		pthread_mutex_lock(&philo->mutex);
		if (g_philosophers.limit && check_meal())
		{
			msg(philo, OVER);
			run_monitor_helper();
		}
		if (!g_philosophers.stop &&
				get_timestamp() - philo->last_eat > g_philosophers.time_to_die)
		{
			msg(philo, DIE);
			run_monitor_helper();
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(2000);
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
	usleep(philo->id * 140);
	while (!g_philosophers.stop)
	{
		if (!g_philosophers.stop)
			take_forks(philo);
		if (!g_philosophers.stop)
			eat(philo);
		if (!g_philosophers.stop)
			put_down_forks(philo);
		if (!g_philosophers.stop)
			sleep_and_think(philo);
	}
	return (NULL);
}

static void	run_threads(void)
{
	int i;

	i = -1;
	while (++i < g_philosophers.number_of_philosophers)
	{
		pthread_create(&(g_philosophers.philos[i].thread), NULL, &run_philo,
				&(g_philosophers.philos[i]));
	}
}

int			main(int argc, char **argv)
{
	parse_args(argc, argv);
	init_philosophers();
	run_threads();
	free_philosophers();
	return (0);
}
