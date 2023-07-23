/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:56:50 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/23 14:36:29 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * can set the stop_simulation value to true if the flag say so
 * copying the stop_simulation var is necessary in order to protect it
 * return the value of the var
 */
int	stop_simulation(t_env *env, bool flag)
{
	int	temp;

	pthread_mutex_lock(&env->mutex_stop_sim);
	if (flag == true)
		env->stop_sim = true;
	temp = env->stop_sim;
	pthread_mutex_unlock(&env->mutex_stop_sim);
	return (temp);
}

bool	is_philo_dead(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	if ((get_time_ms() - philo->last_meal) >= env->time_to_die)
	{
		stop_simulation(env, true);
		print_action(env, philo, DIED, true);
		pthread_mutex_unlock(&philo->mutex_meal);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (false);
}

bool	is_philo_full(t_env *env, t_philo *philo)
{
	if (env->max_meal == -1)
		return (false);
	pthread_mutex_lock(&philo->mutex_meal);
	if (philo->nb_meal >= env->max_meal)
	{
		philo->sated = true;
		pthread_mutex_unlock(&philo->mutex_meal);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (false);
}

bool	are_philo_full(t_env *env)
{
	t_philo	*philo;
	int		i;

	philo = env->philo;
	i = -1;
	while (++i < env->nb_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_meal);
		if (philo[i].sated == false)
		{
			pthread_mutex_unlock(&philo[i].mutex_meal);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].mutex_meal);
	}
	stop_simulation(env, true);
	return (true);
}

void	philo_loop(t_env *env)
{
	int	i;

	start_synchro(env->start_time_ms);
	while (stop_simulation(env, false) == false)
	{
		i = -1;
		while (++i < env->nb_philo)
		{
			if (is_philo_dead(env, &env->philo[i]) || are_philo_full(env))
				return ;
		}
	}
}

//stop_simulation(env, false) == false && 
