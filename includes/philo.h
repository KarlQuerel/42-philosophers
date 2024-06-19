/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:38:16 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 16:32:53 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/* Structures */
struct	s_data;

/* Struct for each philo */
typedef struct s_philo
{
	int				id;
	pthread_t		id_thread;
	long long int	last_eat;
	long long int	nb_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*inf;
}	t_philo;

/* General struct */
typedef struct s_data
{
	int				nb_philo;
	long			t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	unsigned int	n_must_eat;
	int				status;
	long long int	t_start;
	long long int	done;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_mutex_t	eat;
	pthread_mutex_t	start;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

long long int	ft_usleep(long long int time, t_data *data);
long long int	get_converted_time(t_data *data);
int				ft_atoi(char *s);
int				threads_init(t_data *data);
void			threads_join(t_data *data, pthread_t t_id);
int				check_meals(t_data *tmp);
int				check_dead(t_data *data);
void			*routine_monitor(void *data);
void			msg_error(char *s, t_data *data, int fd);
void			ft_print(char *s, t_philo *philo);
void			ft_free(t_data *data);
void			ft_end(t_data *data);
void			*routine_thread(void *data);
void			routine(t_philo *tmp);
void			thr_init_cont(t_data *data);
void			miam_one(t_philo *philo);
void			miam(t_philo *philo);
void			get_forks(t_philo *philo);
void			fork_init_2(t_data *data);
int				arg_check(char **av, t_data *data);
int				fork_init(t_data *data);
int				ft_malloc(t_data *data);
int				philo_init(t_data *data);

#endif