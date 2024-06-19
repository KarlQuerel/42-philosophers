/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:12:46 by kquerel           #+#    #+#             */
/*   Updated: 2023/09/29 17:35:45 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Thread for each philosopher
We split the number of philos according even and odd */
void	*routine_thread(void *data)
{
	t_philo	*tmp;

	tmp = (t_philo *)data;
	pthread_mutex_lock(&tmp->inf->start);
	pthread_mutex_unlock(&tmp->inf->start);
	if (tmp->inf->nb_philo == 1)
		miam_one(tmp);
	if (tmp->inf->nb_philo > 1)
	{
		if (tmp->id % 2 != 0)
			ft_usleep(tmp->inf->t_to_eat, tmp->inf);
		pthread_mutex_lock(&tmp->inf->lock);
		while (tmp->inf->status == 0)
			routine(tmp);
		pthread_mutex_unlock(&tmp->inf->lock);
	}
	return (NULL);
}

/* Routine for each philo, ft_usleep is used depending on the activity
 ft_usleep + 1 is used to fluidify certain precise case */
void	routine(t_philo *tmp)
{
	pthread_mutex_unlock(&tmp->inf->lock);
	check_meals(tmp->inf);
	miam(tmp);
	check_meals(tmp->inf);
	pthread_mutex_lock(&tmp->inf->lock);
	if (tmp->inf->status == 1)
		return ;
	pthread_mutex_unlock(&tmp->inf->lock);
	ft_print("is sleeping", tmp);
	ft_usleep(tmp->inf->t_to_sleep, tmp->inf);
	check_meals(tmp->inf);
	pthread_mutex_lock(&tmp->inf->lock);
	if (tmp->inf->status == 1)
		return ;
	pthread_mutex_unlock(&tmp->inf->lock);
	ft_print("is thinking", tmp);
	ft_usleep(1, tmp->inf);
	ft_usleep(tmp->inf->t_to_eat - tmp->inf->t_to_sleep + 1, tmp->inf);
	pthread_mutex_lock(&tmp->inf->lock);
}

/* Case for one philo */
void	miam_one(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print("has taken a fork", philo);
	pthread_mutex_unlock(philo->r_fork);
}

/* Main function for eating 
Depending on if its odd or even we unlock a left or right fork first*/
void	miam(t_philo *philo)
{
	get_forks(philo);
	check_meals(philo->inf);
	pthread_mutex_lock(&philo->inf->last_meal);
	philo->last_eat = get_converted_time(philo->inf);
	pthread_mutex_unlock(&philo->inf->last_meal);
	ft_usleep(philo->inf->t_to_eat, philo->inf);
	check_meals(philo->inf);
	if (philo->id == philo->inf->nb_philo || philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

/* Changes the order of the first fork taken 
depending on odd or even philo id 
Also check if nb_eat == n_must_eat (av[5]), if its the case increment
the number of philo that are finished (done++)*/
void	get_forks(t_philo *philo)
{
	if (philo->id == philo->inf->nb_philo || philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_print("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		ft_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		ft_print("has taken a fork", philo);
	}
	pthread_mutex_lock(&philo->inf->eat);
	philo->nb_eat = philo->nb_eat + 1;
	ft_print("is eating", philo);
	if (philo->nb_eat == philo->inf->n_must_eat && philo->inf->n_must_eat > 0)
		philo->inf->done = philo->inf->done + 1;
	pthread_mutex_unlock(&philo->inf->eat);
}
