/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:08:02 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/24 10:33:33 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

bool	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ERROR);
	i = 0;
	while (++i < argc)
		if (!is_int(argv[i]))
			return (ERROR);
	return (SUCCESS);
}

/*
 * fill the env struct with presets and infos given by the user
 * can return an error if info aren't valid
 */
int	parse_fct(char **argv, int argc, t_env *env)
{
	env->mutex_tab_fork = NULL;
	env->philo = NULL;
	if (check_args(argc, argv) != SUCCESS)
		return (ERROR);
	env->nb_philo = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (env->nb_philo < 1 || env->nb_philo > 200 || env->time_to_die < 0 \
		|| env->time_to_eat < 0 || env->time_to_sleep < 0)
		return (ERROR);
	if (argc == 6)
	{
		env->max_meal = ft_atoi(argv[5]);
		if (env->max_meal < 0)
			return (ERROR);
	}
	else
		env->max_meal = -1;
	env->stop_sim = false;
	return (SUCCESS);
}
