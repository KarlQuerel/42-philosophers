/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:37:09 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 17:18:55 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Checks validity of each arguments and sets them accordingly 
if av[5] is not present, it is set to -1 */
int	arg_check(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->status = 0;
	data->done = -1;
	if (av[5])
	{
		data->n_must_eat = ft_atoi(av[5]);
		data->done = 0;
	}
	else
		data->n_must_eat = -1;
	if (data->nb_philo <= 0 || data->nb_philo > 200 || data->t_to_die < 0 || \
	data->t_to_eat < 0 || data->t_to_sleep < 0 || data->n_must_eat == 0)
	{
		msg_error("Incorrect arguments", data, 2);
		return (0);
	}
	return (1);
}

/* Function to init all forks */
int	fork_init(t_data *data)
{
	int	i;

	if (!ft_malloc(data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			msg_error("Mutex failed to initiate", data, 2);
			free(data->forks);
			free(data->philo);
			return (0);
		}
		i++;
	}
	fork_init_2(data);
	return (1);
}

/* Functions to malloc philo struct and forks */
int	ft_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
	{
		msg_error("Philo failed to malloc", data, 2);
		return (0);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		msg_error("Forks failed to malloc", data, 2);
		free(data->philo);
		return (0);
	}
	return (1);
}

/* Functions that initiates each mutex and assigns id to each philo
+ 1 to start printing from philo nb 1
it also assigns the converted time to the last time a philo ate */
int	philo_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print, NULL) != 0 || \
		pthread_mutex_init(&data->lock, NULL) != 0 || \
		pthread_mutex_init(&data->start, NULL) != 0 || \
		pthread_mutex_init(&data->eat, NULL) != 0 || \
		pthread_mutex_init(&data->last_meal, NULL) != 0)
	{
		msg_error("Mutex failed to init", data, 2);
		free(data->forks);
		free(data->philo);
		return (0);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = get_converted_time(data);
		data->philo[i].nb_eat = 0;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 4 || ac >= 7)
	{
		msg_error("Invalid number of arguments", &data, 2);
		return (0);
	}
	if (!arg_check(av, &data))
		return (0);
	if (!fork_init(&data))
		return (0);
	if (!philo_init(&data))
		return (0);
	if (!threads_init(&data))
		return (0);
	ft_end(&data);
	return (1);
}
