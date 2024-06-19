/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:53:20 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 17:28:44 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Routine functon for pthread_create
 */
void	*routine_monitor(void *data)
{
	t_data	*tmp;

	tmp = (t_data *)data;
	pthread_mutex_lock(&tmp->lock);
	while (tmp->status == 0)
	{
		pthread_mutex_unlock(&tmp->lock);
		ft_usleep(1, tmp);
		if (check_meals(tmp))
			return (NULL);
		if (check_dead(tmp))
			return (NULL);
		pthread_mutex_lock(&tmp->lock);
	}
	pthread_mutex_unlock(&tmp->lock);
	return (NULL);
}

/* Creates and sends threads unto the routine function.
One thread to monitor on each philo
One thread for each philosopher
Locks start mutex first while initiating threads to insure all philosophers
start at the same time */
int	threads_init(t_data *data)
{
	int			i;
	t_data		*tmp;
	pthread_t	t_id;

	i = 0;
	tmp = data;
	pthread_mutex_lock(&data->start);
	data->t_start = get_converted_time(data);
	if (pthread_create(&t_id, NULL, &routine_monitor, tmp) != 0)
		return (thr_init_cont(data), 0);
	while (i < data->nb_philo)
	{
		data->philo[i].inf = data;
		if (pthread_create(&data->philo[i].id_thread, NULL, &routine_thread, \
		&data->philo[i]) != 0)
			return (thr_init_cont(data), 0);
		i++;
	}
	pthread_mutex_unlock(&data->start);
	threads_join(data, t_id);
	return (1);
}

/* Functions to join threads 
phtread_join waits for a thread to terminate, detachs it and then 
returns the thread exit status 
(unless we enter NULL as a 2nd parameter like we did) */
void	threads_join(t_data *data, pthread_t t_id)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].id_thread, NULL) != 0)
		{
			msg_error("Joining threads has failed", data, 2);
			free (data->forks);
			free (data->philo);
			return ;
		}
		i++;
	}
	if (pthread_join(t_id, NULL) != 0)
	{
		msg_error("Joining threads has failed", data, 2);
		free (data->forks);
		free (data->philo);
		return ;
	}
}

/* Checks if all meals has been eaten (av[5]) */
int	check_meals(t_data *tmp)
{
	pthread_mutex_lock(&tmp->eat);
	if (tmp->n_must_eat > 0 && tmp->done >= tmp->nb_philo)
	{
		pthread_mutex_unlock(&tmp->eat);
		pthread_mutex_lock(&tmp->lock);
		tmp->status = 1;
		pthread_mutex_unlock(&tmp->lock);
		return (1);
	}
	pthread_mutex_unlock(&tmp->eat);
	return (0);
}

/* Checks if a philo is dead
if current time - last_eat >= t_to_die, it means a philo died
so status is set to 1 and we stop the simulation */
int	check_dead(t_data *data)
{
	char			*s;
	int				i;
	long long int	time;

	s = "is dead";
	pthread_mutex_lock(&data->last_meal);
	time = get_converted_time(data);
	i = 0;
	while (i < data->nb_philo)
	{
		if ((time - (data->philo[i]).last_eat) >= data->t_to_die)
		{
			pthread_mutex_unlock(&data->last_meal);
			pthread_mutex_lock(&data->lock);
			data->status = 1;
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_lock(&data->print);
			printf("%lld %d %s\n", time - data->t_start, (data->philo[i]).id, s);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->last_meal);
	return (0);
}
