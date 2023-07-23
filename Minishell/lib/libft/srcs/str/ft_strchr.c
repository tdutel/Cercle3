/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:17:07 by gd-harco          #+#    #+#             */
/*   Updated: 2022/10/22 19:17:07 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @function ft_strchr
 * @brief Locate the last occurrence of the character c in the string s.
 * @param s The string to be searched in.
 * @param c The character to be searched for.
 * @return A pointer to the first occurrence of the character c in the string s,
 * NULL if the character isn't found.
 * @author gd-harco
 */

char	*ft_strchr(const char *s, int c)
{
	if (c % 256 == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (c % 256))
			return ((char *) s);
		s++;
	}
	return (NULL);
}
