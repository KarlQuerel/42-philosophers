/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:12:21 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 17:25:59 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Slightly modified atoi for philo projects */
int	ft_atoi(char *s)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + s[i] - '0';
		if (nb > INT_MAX || nb < INT_MIN)
			return (0);
		i++;
	}
	if (s[i])
		nb = 0;
	return (nb * sign);
}

/* More precise usleep fonction */
long long int	ft_usleep(long long int time, t_data *data)
{
	long long int	time_start;

	time_start = get_converted_time(data);
	while ((get_converted_time(data) - time_start) < time)
	{
		pthread_mutex_lock(&data->lock);
		if (data->status == 1)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(500);
	}
	return (0);
}

/* Function to get the current time in seconds */
long long int	get_converted_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		msg_error("gettimeofday failed", data, 2);
		free(data->forks);
		free(data->philo);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* Classic ft_free */
void	ft_free(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

/* Destroys all mutexes and calls ft_free 
pthread_mutex_destroy destroys the unlocked mutex */
void	ft_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->nb_philo < 1)
		pthread_mutex_unlock(&data->print);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->last_meal);
	pthread_mutex_destroy(&data->start);
	ft_free(data);
}
