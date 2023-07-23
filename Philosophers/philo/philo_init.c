/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/30 14:16:27 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	unsigned int	i;
	int				n;
	int				res;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = n * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * n);
}

int	init_mutexs(t_ph *s_ph)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(s_ph->cont->mutex_write), NULL);
	pthread_mutex_init(&(s_ph->cont->lock_all_meal), NULL);
	pthread_mutex_init(&(s_ph->cont->check_dead), NULL);
	s_ph->cont->forks = malloc(sizeof(pthread_mutex_t) \
		* s_ph->cont->nb_forks);
	if (!s_ph->cont->forks)
		return (-1);
	s_ph->cont->time_lock = malloc(sizeof(pthread_mutex_t) \
	* s_ph->cont->nb_forks);
	if (!s_ph->cont->time_lock)
	{
		free(s_ph->cont->forks);
		return (-1);
	}
	while (i < s_ph->cont->nb_forks)
	{
		pthread_mutex_init(&(s_ph->cont->forks[i]), NULL);
		pthread_mutex_init(&(s_ph->cont->time_lock[i]), NULL);
		i++;
	}
	return (0);
}

int	forks(t_ph *s_ph)
{
	int	i;

	s_ph->cont->tab_forks = malloc(sizeof(int) * s_ph->cont->nb_forks);
	if (!s_ph->cont->tab_forks)
	{
		free(s_ph->cont->forks);
		free(s_ph->cont->time_lock);
		return (-1);
	}
	i = 0;
	while (i < s_ph->cont->nb_forks)
	{
		s_ph->cont->tab_forks[i] = 1;
		i++;
	}
	s_ph->right_hand = 0;
	s_ph->left_hand = 0;
	return (0);
}

int	init_struc_elms(int argc, char **argv, t_ph *s_ph)
{
	s_ph->nb_philo = ft_atoi(argv[1]);
	s_ph->cont->nb_forks = s_ph->nb_philo;
	s_ph->time_die = ft_atoi(argv[2]) * 1000;
	s_ph->time_eat = ft_atoi(argv[3]) * 1000;
	s_ph->time_sleep = ft_atoi(argv[4]) * 1000;
	s_ph->id = 1;
	s_ph->nb_food_eaten = 0;
	s_ph->cont->eat_all_meal = 0;
	s_ph->max_food_to_eat = -1;
	if (argc == 6)
		s_ph->max_food_to_eat = ft_atoi(argv[5]);
	if (check_min_values(s_ph, argc, argv) == -1)
		return (-1);
	if (check_max_values(s_ph) == -1)
		return (-1);
	if (init_mutexs(s_ph) == -1)
		return (-1);
	s_ph->start_time = get_time();
	s_ph->last_meal = s_ph->start_time;
	s_ph->cont->checker = 0;
	forks(s_ph);
	return (0);
}
