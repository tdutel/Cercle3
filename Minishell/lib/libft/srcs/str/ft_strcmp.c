/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:27:39 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/12 16:10:01 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @function ft_strcmp
 * @brief Compare two strings.
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return 0 if the strings are identical,
 * otherwise the difference between the first two differing bytes.
 * @author gd-harco
 */

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*(unsigned char *)s1 + *(unsigned char *)s2 != 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
