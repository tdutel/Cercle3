/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:33:01 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/29 14:54:07 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_ph phi, pthread_t *philos, t_ph *tab_philos)
{
	free(tab_philos);
	free(phi.cont->forks);
	free(phi.cont->time_lock);
	free(phi.cont->tab_forks);
	free(philos);
}

int	free_tab_philos(t_ph *phi, pthread_t **philosophers)
{
	free(phi->cont->forks);
	free(phi->cont->tab_forks);
	free(phi->cont->time_lock);
	free(philosophers);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*philosophers;
	t_ph			phi;
	t_ph			*tab_philos;
	t_cont		cont;

	phi.cont = &cont;
	if (parse(argc, argv) == -1)
		return (0);
	if (init_struc_elms(argc, argv, &phi) == -1)
		return (0);
	philosophers = malloc(sizeof(pthread_t) * phi.nb_philo);
	if (!philosophers)
	{
		free(phi.cont->forks);
		free(phi.cont->tab_forks);
		free(phi.cont->time_lock);
		return (0);
	}
	tab_philos = malloc(sizeof(t_ph) * phi.nb_philo);
	if (!tab_philos)
		return (free_tab_philos(&phi, &philosophers));
	exec(&phi, philosophers, tab_philos);
	ft_free(phi, philosophers, tab_philos);
}
