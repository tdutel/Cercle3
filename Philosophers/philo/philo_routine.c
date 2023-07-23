/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:39:12 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/30 14:16:55 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	execute_routine(t_ph *philo)
{
	while (1)
	{
		eat(philo);
		if (philo->max_food_to_eat != -1)
			philo->nb_food_eaten++;
		if (philo->nb_food_eaten == philo->max_food_to_eat)
		{
			pthread_mutex_lock(&(philo->cont->lock_all_meal));
			philo->cont->eat_all_meal++;
			pthread_mutex_unlock(&(philo->cont->lock_all_meal));
		}
		if (sleeping(philo) == -1)
			break ;
		if (think(philo) == -1)
			break ;
	}
	release_all_fork(philo);
}

void	execute_routine_for_one(t_ph *philo)
{
	print_state(philo, TAKE_F);
	usleep(philo->time_die);
}

void	*routine(void *phi)
{
	t_ph	*philo;

	philo = (t_ph *) phi;
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->nb_philo == 1)
		execute_routine_for_one(philo);
	else
		execute_routine(philo);
	return (0);
}

void	*do_death(t_ph *philo, int i)
{
	pthread_mutex_unlock(&(philo->cont->time_lock[i]));
	pthread_mutex_unlock(&(philo->cont->lock_all_meal));
	pthread_mutex_lock(&(philo->cont->check_dead));
	philo[i].cont->checker = 1;
	pthread_mutex_unlock(&(philo->cont->check_dead));
	pthread_mutex_lock(&(philo->cont->lock_all_meal));
	if (philo->cont->eat_all_meal != philo->nb_philo)
	{
		if (print_state(&philo[i], DIE) == -1)
		{
			pthread_mutex_unlock(&(philo->cont->lock_all_meal));
			return (0);
		}
	}
	pthread_mutex_unlock(&(philo->cont->lock_all_meal));
	return (0);
}

void	*check_dead(void *phi)
{
	t_ph	*philo;
	int		i;

	philo = phi;
	while (1)
	{
		usleep(100);
		i = 0;
		while (i < philo[0].nb_philo)
		{
			pthread_mutex_lock(&(philo->cont->time_lock[i]));
			pthread_mutex_lock(&(philo->cont->lock_all_meal));
			if (((get_time() - philo[i].last_meal) * 1000) > \
				((unsigned long long)philo[i].time_die) \
				|| (philo->cont->eat_all_meal == philo->nb_philo))
			{
				return (do_death(philo, i));
			}
			pthread_mutex_unlock(&(philo->cont->time_lock[i]));
			pthread_mutex_unlock(&(philo->cont->lock_all_meal));
			i++;
		}
	}
	return (0);
}
