/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:13:23 by vgoldman          #+#    #+#             */
/*   Updated: 2020/11/05 18:55:32 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdint.h>

# ifdef __APPLE__
#  define DELAY_MONITOR 1500
#  define DELAY_START 0
#  define DELAY_SLEEP 500
# endif

# ifdef __linux__
#  define DELAY_MONITOR 1500
#  define DELAY_START 500
#  define DELAY_SLEEP 500
# endif

typedef pthread_mutex_t	t_mutex;

typedef struct			s_philo
{
	int			id;
	char		*id_str;
	int			iter;
	int			last_eat;
	pthread_t	thread;
	sem_t		*mutex;
	pid_t		pid;
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
	sem_t		*forks;
	sem_t		*msg;
}						t_philosophers;

enum					e_states
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	OVER
};

void					parse_args(int argc, char **argv);
void					err(const char *msg);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
void					init_philosophers(void);
void					*run_philo(void *arg);
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					put_down_forks(void);
void					sleep_and_think(t_philo *philo);
void					msg(t_philo *philo, int type);
int						ft_strlen(char *str);
uint64_t				get_time(void);
int						get_timestamp(void);
void					free_philosophers(void);
void					ft_sleep(int ms);
void					run_monitor_helper(void);
char					*prefix(char *id);
void					run_threads(void);
void					*run_meal_counter(void *arg);
int						check_meal(void);

#endif
