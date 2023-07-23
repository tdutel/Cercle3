/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:34:03 by tdutel            #+#    #+#             */
/*   Updated: 2023/03/29 12:38:08 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_parse(const char *str)
{
	unsigned int		i;
	int					n;
	unsigned long long	res;

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
	if (res > (unsigned long long)2147483647)
		return (-1);
	return (res * n);
}

int	check_max_values(t_ph *s_ph)
{
	if (s_ph->time_eat > 10000000 || s_ph->time_sleep > 10000000 \
	|| s_ph->nb_philo > 200)
	{
		if (s_ph->time_eat > 10000000)
			write(2, "Time to eat is too big\n", 23);
		else if (s_ph->time_sleep > 10000000)
			write(2, "Time to sleep is too big\n", 25);
		else if (s_ph->nb_philo > 200)
			write(2, "Too much philosophers\n", 22);
		return (-1);
	}
	else
		return (0);
}

int	check_min_values(t_ph *s_ph, int argc, char **argv)
{
	if (s_ph->nb_philo < 1 || s_ph->time_die < 60000 || s_ph->time_eat < 60000 \
		|| s_ph->time_sleep < 60000 || (argc == 6 && ft_atoi(argv[5]) < 1))
	{
		if (s_ph->nb_philo < 1)
			write(2, "Too few philosophers\n", 21);
		else if (s_ph->time_die < 60000)
			write(2, "Time to die is too short\n", 25);
		else if (s_ph->time_eat < 60000)
			write(2, "Time to eat is too short\n", 25);
		else if (s_ph->time_sleep < 60000)
			write(2, "Time to sleep is too short\n", 27);
		else if (argc == 6 && ft_atoi(argv[5]) < 1)
			write(2, "Too few meal to eat\n", 20);
		return (-1);
	}
	else
		return (0);
}

int	check_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '-')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of paramaters\n", 27);
		return (-1);
	}
	if (check_num(argv) == -1)
	{
		write(2, "Wrong parameters\n", 17);
		return (-1);
	}
	i = 0;
	while (argv[i])
	{
		if (atoi_parse(argv[i]) == -1)
		{
			write(2, "ERROR : int value require\n", 26);
			return (-1);
		}
		i++;
	}
	return (0);
}
