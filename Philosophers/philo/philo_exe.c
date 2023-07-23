/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:57 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/29 14:54:07 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_ph *s_ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(s_ph->cont->mutex_write));
	pthread_mutex_destroy(&(s_ph->cont->lock_all_meal));
	pthread_mutex_destroy(&(s_ph->cont->check_dead));
	while (i < s_ph->cont->nb_forks)
	{
		pthread_mutex_destroy(&(s_ph->cont->forks[i]));
		pthread_mutex_destroy(&(s_ph->cont->time_lock[i]));
		i++;
	}
}

int	join_pthread(t_ph *s_ph, pthread_t *cont, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < s_ph->nb_philo)
	{	
		if (pthread_join(philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(*cont, NULL) != 0)
		return (-1);
	return (0);
}

int	free_cont(t_ph *s_ph, pthread_t *phis, t_ph *tab_phis)
{
	free(s_ph->cont->forks);
	free(s_ph->cont->tab_forks);
	free(phis);
	free(tab_phis);
	return (-1);
}

int	exec(t_ph *s_ph, pthread_t *philos, t_ph *tab_philos)
{
	pthread_t	*cont;
	int			i;

	i = 0;
	cont = malloc(sizeof(pthread_t));
	if (!cont)
		return (free_cont(s_ph, philos, tab_philos));
	while (i < s_ph->nb_philo)
	{
		tab_philos[i] = *s_ph;
		tab_philos[i].id = i + 1;
		if (pthread_create(&philos[i], NULL, routine, &tab_philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(cont, NULL, check_dead, tab_philos) != 0)
		return (-1);
	if (join_pthread(s_ph, cont, philos) == -1)
		return (-1);
	destroy_mutex(s_ph);
	free(cont);
	return (0);
}
