/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:11:10 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 17:36:23 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Prints the msg error followed by the string on the 
file descriptor passed in parameters */
void	msg_error(char *s, t_data *data, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		write(fd, "Error!\n", 7);
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
		write (fd, "\n", 1);
		return ;
	}
	if (data->status == 0)
		return ;
}

/* Functions to print s passed in argument
Checks if status == 0 before printing */
void	ft_print(char *s, t_philo *philo)
{
	long long int	t;

	pthread_mutex_lock(&philo->inf->lock);
	pthread_mutex_lock(&philo->inf->print);
	if (philo->inf->status == 0)
	{
		t = get_converted_time(philo->inf);
		printf("%lld %d %s\n", t - philo->inf->t_start, philo->id, s);
	}
	pthread_mutex_unlock(&philo->inf->lock);
	pthread_mutex_unlock(&philo->inf->print);
}

/* fork_init_continued
if we are on the last philo, his l_fork is assigned as the first fork
in the fork array */
void	fork_init_2(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].r_fork = &data->forks[i];
		if (i == data->nb_philo - 1)
			data->philo[i].l_fork = &data->forks[0];
		else
			data->philo[i].l_fork = &data->forks[i + 1];
		i++;
	}
}

/* threads_continued for norminette */
void	thr_init_cont(t_data *data)
{
	msg_error("Thread creation failed", data, 2);
	free (data->forks);
	free (data->philo);
}
