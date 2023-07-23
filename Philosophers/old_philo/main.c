/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:24 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/23 14:38:06 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_launcher(t_env *env, t_philo *philo)
{
	int	i;

	env->start_time_ms = get_time_ms() + 500;
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create \
		(&philo[i].thread_id, NULL, &philosopher, &(philo[i])))
			return (ERROR);
	}
	philo_loop(env);
	return (SUCCESS);
}

int	end_simulation(t_env *env, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	env;
	t_philo	*philo;

	if (parse_fct(argv, argc, &env))
		return (write_error(STR_ERR_SYNTAX, &env));
	if (init_philo(&env, &philo))
		return (ERROR);
	if (sim_launcher(&env, philo))
		return (ERROR);
	if (end_simulation(&env, philo))
		return (ERROR);
	clean(&env);
	return (SUCCESS);
}
