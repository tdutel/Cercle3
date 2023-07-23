/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:35:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/29 12:38:28 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time)
{
	long long	i;

	time /= 1000;
	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break ;
		usleep(50);
	}
}

long long	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}
