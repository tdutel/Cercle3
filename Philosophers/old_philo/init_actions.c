/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:31:18 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/23 14:54:34 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_env *env)
{
	int	i;

	env->mutex_tab_fork = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->mutex_tab_fork)
		return (ERROR);
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_mutex_init(&env->mutex_tab_fork[i], 0))
			return (ERROR);
	if (pthread_mutex_init(&env->mutex_stop_sim, 0))
		return (ERROR);
	if (pthread_mutex_init(&env->mutex_print, 0))
		return (ERROR);
	return (SUCCESS);
}

/*
 * assigning forks for odd and even philo must be different
 * otherwise it can lead to deadlock
 * e.g : a philo lock the mutex of his first fork, then wait for the second one
 * but it had been taken by a second philo who's now waiting for the first one
 */
void	init_forks_fct(t_env *env, t_philo *philo, int id_philo)
{
	if (id_philo % 2 == 1)
	{
		philo->right_fork_id = id_philo;
		philo->left_fork_id = (id_philo % env->nb_philo) + 1;
	}
	else
	{
		philo->right_fork_id = (id_philo % env->nb_philo) + 1;
		philo->left_fork_id = id_philo;
	}
}

int	init_philo(t_env *env, t_philo **philo)
{
	int	i;
	int	id;

	*philo = malloc(sizeof(**philo) * env->nb_philo);
	if (!*philo)
		return (write_error(STR_ERR_MALLOC, env));
	i = -1;
	while (++i < env->nb_philo)
	{
		id = i + 1;
		(*philo)[i].index = id;
		(*philo)[i].env = env;
		init_forks_fct(env, &(*philo)[i], id);
		(*philo)[i].last_meal = -1;
		if (pthread_mutex_init(&(*philo)[i].mutex_meal, 0))
			return (write_error(STR_ERR_MUTEX_INIT, env));
	}
	env->philo = *philo;
	if (mutex_init(env))
		return (write_error(STR_ERR_MUTEX_INIT, env));
	(*philo)[i].sated = false;
	(*philo)[i].nb_meal = 0;
	return (SUCCESS);
}

void	eating_fct(t_env *env, t_philo *philo)
{
	if (env->nb_philo == 1)
		return ;
	pthread_mutex_lock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	print_action(env, philo, FORK, 0);
	pthread_mutex_lock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
	print_action(env, philo, FORK, 0);
	print_action(env, philo, EAT, 0);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	usleep_plus(env->time_to_eat);
	philo->nb_meal++;
	is_philo_full(env, philo);
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
}

void	print_action(t_env *env, t_philo *philo, t_action act, bool died)
{
	static char	*tab_action[] = {"is eating", "has taken a fork", \
		"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&env->mutex_print);
	if (stop_simulation(env, false) == true && died == false)
	{
		pthread_mutex_unlock(&env->mutex_print);
		return ;
	}
	printf("%li %i %s\n", \
	get_time_ms() - env->start_time_ms, philo->index, tab_action[act]);
	pthread_mutex_unlock(&env->mutex_print);
}
