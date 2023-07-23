/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:41:08 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/23 10:51:55 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	long	sign;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (sign * res);
}

time_t	get_time_ms(void)
{
	t_tval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	usleep_plus(time_t usec)
{
	time_t	timestamp;

	timestamp = get_time_ms() + usec;
	while (get_time_ms() < timestamp)
		usleep(100);
}

bool	clean(t_env *env)
{
	int	i;

	if (pthread_mutex_destroy(&env->mutex_print))
		return (ERROR);
	if (pthread_mutex_destroy(&env->mutex_stop_sim))
		return (ERROR);
	i = 0;
	while (++i < env->nb_philo)
	{
		if (pthread_mutex_destroy(&env->mutex_tab_fork[i]))
			return (ERROR);
		if (pthread_mutex_destroy(&env->philo[i].mutex_meal))
			return (ERROR);
	}
	free (env->mutex_tab_fork);
	free (env->philo);
	return (SUCCESS);
}

int	write_error(char *str, t_env *env)
{
	clean(env);
	printf("%s\n", str);
	return (ERROR);
}
