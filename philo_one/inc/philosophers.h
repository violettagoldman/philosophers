/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:13:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/09/26 18:34:32 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct			s_philo
{
	int			id;
	int			iter;
	int			last_eat;
	pthread_t	thread;
	t_mutex		mutex;
}						t_philo;

typedef struct			s_philosophers
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_time_each_philosopher_must_eat;
	int			number_of_philosophers;
	int			limit;
	int			stop;
	uint64_t	start;
	t_philo		*philos;
	t_mutex		*forks;
	t_mutex		msg;
	t_mutex		die;
}						t_philosophers;

enum states {FORK, EAT, SLEEP, THINK, DIE};

void					parse_args(int argc, char **argv);
void					err(const char *msg);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
void					init_philosophers(void);
void					*run_philo(void *arg);
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					put_down_forks(t_philo *philo);
void					sleep_and_think(t_philo *philo);
void					msg(t_philo *philo, int type);
int						ft_strlen(char *str);
uint64_t				get_time(void);
int						get_timestamp(void);
void					free_philosophers(void);

#endif