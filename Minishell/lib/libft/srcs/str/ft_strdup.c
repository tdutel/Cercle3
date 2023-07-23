/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:46 by gd-harco          #+#    #+#             */
/*   Updated: 2022/11/07 15:26:39 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @function ft_strdup
 * @brief Allocate (with malloc(3)) and returns
 * a NULL-terminated copy of string s1.
 * @param s1 The string to be duplicated.
 * @return The pointer to the new string. \n
 * NULL if the allocation fails or if s1 is NULL.
 * @author gd-harco
 */
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		x;

	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2 || !s1)
	{
		if (s2)
			free(s2);
		return (NULL);
	}
	x = 0;
	while (s1[x])
	{
		s2[x] = s1[x];
		x++;
	}
	s2[x] = '\0';
	return (s2);
}
